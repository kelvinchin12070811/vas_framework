#pragma once
#include <boost/optional.hpp>
#include <map>
#include "State.hpp"
#include "StateConditionalTransition.hpp"

namespace vas
{
	/** @addtogroup animate
		  @{
	*/
	/** @brief The state machine implementation of animation controller. */
	class StateAnimator
	{ /** @} */
	public:
		StateAnimator();

		/** Set the conditional variable. This action might trigger transition of animation.
			  @param name Name of the conditional variable.
			  @param value The value of the conditional variable.
		*/
		void setConditionalVar(const std::string& name, std::any value);
		/** Get the conditional variable.
			  @param name Name of the conditional variable.
		*/
		const std::any& getConditionalVar(const std::string& name) const;

		/** Insert new transition between two state.
			  @param name Name of the transition.
			  @param transition Transition detial about the transition.
			  @param condiVar Related conditional variable, trigger if it changed.
		*/
		void insertTransition(const std::string& name, StateConditionalTransition transition, const std::string& condiVar);
		/** Get the transition information. Throw std::out_of_range if failed.
			 @param name name of the transition.
		*/
		const StateConditionalTransition& getTransition(const std::string& name) const;

		/** Get current running animation.
			  @retval boost::optional Iterator to current state or empty if failed.
		*/
		boost::optional<std::map<std::string, State>::const_iterator> currentAnimation() const;
	private:
		std::map<std::string, std::any> cdVarList; // Conditional vars list.
		std::map<std::string, State> state; // States
		std::map<std::string, StateConditionalTransition> transitionsList; // Transitions
		std::multimap<std::string, std::string> cdVar2TransitionMap;

		std::map<std::string, State>::iterator curAnim;
	};
}