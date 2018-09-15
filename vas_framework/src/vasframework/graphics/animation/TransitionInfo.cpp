#include "TransitionInfo.hpp"

namespace vas
{
	TransitionInfo::TransitionInfo(const std::string & to, std::function<bool(const std::any&)> condition, bool waitFinish):
		to(to), condition(condition), waitFinish(waitFinish)
	{
	}

	TransitionInfo::~TransitionInfo()
	{
	}

	bool TransitionInfo::conditionAchived(const std::any& param) const
	{
		return condition(param);
	}

	bool TransitionInfo::isWaitUntilFinish() const
	{
		return waitFinish;
	}

	const std::string& TransitionInfo::getTransitionTo() const
	{
		return to;
	}
}