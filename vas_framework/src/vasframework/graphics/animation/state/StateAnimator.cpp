//===========================================================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//===========================================================================================================
#include "StateAnimator.hpp"

namespace vas
{
	StateAnimator::StateAnimator()
	{
		curAnim = state.begin();
	}

	void StateAnimator::setConditionalVar(const std::string & name, std::any value)
	{
		auto begin = cdVar2TransitionMap.lower_bound(name);
		auto end = cdVar2TransitionMap.upper_bound(name);

		for (auto itr = begin; itr != end; itr++)
		{
			StateConditionalTransition* curTransition{ nullptr };
			try
			{
				curTransition = &transitionsList.at(itr->second);
			}
			catch (std::out_of_range&)
			{
				continue;
			}

			if (curTransition->getSrcState() == curAnim->first && curTransition->achieved(value))
			{
				auto result = state.find(curTransition->getDestState());
				if (result != state.end())
				{
					curAnim->second.animation->reset();
					curAnim = result;
					break;
				}
			}
		}
		cdVarList[name] = std::move(value);
	}

	const std::any & StateAnimator::getConditionalVar(const std::string & name) const
	{
		return cdVarList.at(name);
	}

	void StateAnimator::insertTransition(const std::string & name, StateConditionalTransition transition, const std::string & condiVar)
	{
		transitionsList.insert({ name, transition });
		cdVar2TransitionMap.insert({ condiVar, name });
	}

	const StateConditionalTransition & StateAnimator::getTransition(const std::string & name) const
	{
		return transitionsList.at(name);
	}

	std::optional<std::map<std::string, State>::const_iterator> StateAnimator::currentAnimation() const
	{
		if (curAnim == state.end()) return std::nullopt;
		return curAnim;
	}
}