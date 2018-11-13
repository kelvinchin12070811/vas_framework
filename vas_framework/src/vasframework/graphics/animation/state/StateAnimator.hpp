#pragma once
#include <boost/optional.hpp>
#include <map>
#include "State.hpp"
#include "StateConditionalTransition.hpp"

namespace vas
{
	class StateAnimator
	{
	public:
		StateAnimator();
		~StateAnimator();

		void setConditionalVar(const std::string& name, std::any value);
		const std::any& getConditionalVar(const std::string& name) const;

		void insertTransition(const std::string& name, StateConditionalTransition transition, const std::string& condiVar);
		const StateConditionalTransition& getTransition(const std::string& name) const;

		boost::optional<std::map<std::string, State>::const_iterator> currentAnimation() const;
	private:
		std::map<std::string, std::any> cdVarList; // Conditional vars list.
		std::map<std::string, State> state; // States
		std::map<std::string, StateConditionalTransition> transitionsList; // Transitions
		std::multimap<std::string, std::string> cdVar2TransitionMap;

		std::map<std::string, State>::iterator curAnim;
	};
}