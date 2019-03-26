//===========================================================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//===========================================================================================================
#pragma once
#include <optional>
#include <map>
#include "State.hpp"
#include "StateConditionalTransition.hpp"

namespace vas
{
	/**
	 * @ingroup animate
	 * @{
	 */
	/** @brief The state machine implementation of animation controller. */
	class StateAnimator
	{ /** @} */
	public:
		StateAnimator();

		/**
		 * Set the conditional variable. This action might trigger transition of animation.
		 * @param[in] name Name of the conditional variable.
		 * @param[in] value The value of the conditional variable.
		 */
		void setConditionalVar(const std::string& name, std::any value);
		/**
		 * Get the conditional variable.
		 * @param[in] name Name of the conditional variable.
		 */
		const std::any& getConditionalVar(const std::string& name) const;

		/**
		 * Insert new transition between two state.
		 * @param[in] name Name of the transition.
		 * @param[in] transition Transition detial about the transition.
		 * @param[in] condiVar Related conditional variable, trigger if it changed.
		 */
		void insertTransition(const std::string& name, StateConditionalTransition transition, const std::string& condiVar);
		/**
		 * Get the transition information.
		 * @param[in] name name of the transition.
		 * @throw std::out_of_range if @p name not found.
		 */
		const StateConditionalTransition& getTransition(const std::string& name) const;

		/**
		 * Get current running animation.
		 * @retval std::optional Iterator to current state or empty if failed.
		 */
		std::optional<std::map<std::string, State>::const_iterator> currentAnimation() const;
	private:
		std::map<std::string, std::any> cdVarList; // Conditional vars list.
		std::map<std::string, State> state; // States
		std::map<std::string, StateConditionalTransition> transitionsList; // Transitions
		std::multimap<std::string, std::string> cdVar2TransitionMap;

		std::map<std::string, State>::iterator curAnim;
	};
}