#include "StateConditionalTransition.hpp"

namespace vas
{
	StateConditionalTransition::StateConditionalTransition(const std::string & srcState, const std::string & destState, std::function<bool(const std::any&)> validator):
		srcState(srcState), destState(destState), validator(std::move(validator))
	{
	}

	StateConditionalTransition::~StateConditionalTransition()
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