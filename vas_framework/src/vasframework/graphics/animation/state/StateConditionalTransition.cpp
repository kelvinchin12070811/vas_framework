//===========================================================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//===========================================================================================================
#include "StateConditionalTransition.hpp"

namespace vas
{
	StateConditionalTransition::StateConditionalTransition(const std::string & srcState, const std::string & destState, std::function<bool(const std::any&)> validator):
		srcState(srcState), destState(destState), validator(std::move(validator))
	{
	}

	bool StateConditionalTransition::achieved(const std::any & cdVar) const
	{
		return validator == nullptr ? false : validator(cdVar);
	}

	std::string StateConditionalTransition::getSrcState() const
	{
		return srcState;
	}

	std::string StateConditionalTransition::getDestState() const
	{
		return destState;
	}
}