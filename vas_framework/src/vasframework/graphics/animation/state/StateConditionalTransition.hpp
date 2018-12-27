#pragma once
#include <any>
#include <functional>
#include <string>

namespace vas
{
	/** @addtogroup animate
		  @{
	*/
	/** Validate std::any with binded value.
		  @tparam T Type of value to compare.
		  @tparam Predicate Functor that use to compare value.
		  @param value std::any to compare, passed by StateConditionalTransition.
		  @param compare value to compare, constant binded with std::bind.

		  Defined in: vasframework/graphics/animation/state/StateConditionalTransition.hpp
	*/
	template <typename T, typename Predicate = std::equal_to>
	bool defValidator(const std::any& value, const T& compare)
	{
		if (!value.has_value())
			return false;

		if (value.type() == typeid(T))
		{
			Predicate pre;
			return pre(std::any_cast<T>(value), compare);
		}
		return false
	}
	/** @} */

	/** @addtogroup animate
		  @}
	*/
	/** @brief Conditional of a transition to trigger.
		  
		  The StateConditionalTransition is a class that recorded when a transition should be triggered and which
		  animation to transition to.
	*/
	class StateConditionalTransition
	{ /** @} */
	public:
		/** Create transition condition and information.
			  @param srcState Starting state, not triggered if the current state is not the source state.
			  @param destState State that need to transition to.
			  @param validator Validator that validate if transition's condition achived or not. Use vas::defValidator for help
			  or implement your own validator.
		*/
		StateConditionalTransition(const std::string& srcState, const std::string& destState, std::function<bool(const std::any&)> validator);
		/** Chect if the state's condition achived or not. */
		bool achieved(const std::any& cdVar) const;

		std::string getSrcState() const;
		std::string getDestState() const;
	private:
		/** [Read Only] The name of source state of the transition.
				- __accessors__
					-# std::string getSrcState() const
		*/
		std::string srcState;
		/** [Read Only] The name of destination state of the transition.
				- __accessors__
					-# std::string getDestState() const
		*/
		std::string destState;
		std::function<bool(const std::any&)> validator;
	};
}