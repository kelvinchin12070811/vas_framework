//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <any>
#include <functional>
#include <string>

namespace vas
{
	/**
	 * @ingroup animate
	 * @{
	 */
	/**
	 * Validate std::any with binded value.
	 * @tparam T Type of value to compare.
	 * @tparam Predicate Functor that use to compare value.
	 * @param[in] value std::any to compare, passed by StateConditionalTransition.
	 * @param[in] compare value to compare, constant binded with std::bind.
	 * 
	 * Defined in: vasframework/graphics/animation/state/StateConditionalTransition.hpp
	 */
	template <typename T, typename Predicate = std::equal_to<T>>
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

	/**
	 * @ingroup animate
	 * @}
	 */
	/**
	 * @brief Conditional of a transition to trigger.
	 * 
	 * The StateConditionalTransition is a class that recorded when a transition should be triggered and which
	 * animation to transition to.
	 */
	class StateConditionalTransition
	{ /** @} */
	public:
		/**
		 * Create transition condition and information.
		 * @param[in] srcState Starting state, not triggered if the current state is not the source state.
		 * @param[in] destState State that need to transition to.
		 * @param[in] validator Validator that validate if transition's condition achived or not. Use vas::defValidator for help
		 * or implement your own validator.
		 */
		StateConditionalTransition(const std::string& srcState, const std::string& destState, std::function<bool(const std::any&)> validator);
		/** Chect if the state's condition achived or not. */
		bool achieved(const std::any& cdVar) const;

		std::string getSrcState() const;
		std::string getDestState() const;
	private:
		/**
		 * The name of source state of the transition.
		 *
		 * ####Accessors
		 * -# std::string getSrcState() const
		 */
		std::string srcState;
		/**
		 * The name of destination state of the transition.
		 * 
		 * ####Accessors
		 * -# std::string getDestState() const
		 */
		std::string destState;
		std::function<bool(const std::any&)> validator;
	};
}