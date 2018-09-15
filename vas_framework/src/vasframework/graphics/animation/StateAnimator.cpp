#include <exception>
#include <boost/format.hpp>
#include "StateAnimator.hpp"

namespace vas
{
	StateAnimator::StateAnimator()
	{
	}

	StateAnimator::~StateAnimator()
	{
	}

	void StateAnimator::insertTransition(TransitionInfo info, const std::string & mapedParam)
	{
		transitions.insert({ mapedParam, std::move(info) });
	}

	void StateAnimator::triggerParam(const std::string & name)
	{
		auto param = parameters.at(name);
		if (param.has_value())
			throw std::runtime_error((boost::format("The parameter \"%s\" is not a Trigger type") % name).str());

		changeAnimation(name, param);
	}

	void StateAnimator::setParamValue(const std::string & name, std::any value)
	{
		auto param = parameters.at(name);
		if (param.type() != value.type())
			throw std::runtime_error((boost::format("The paramter type passed does not match with the parameter \"%s%\".").str()));
		
		param = std::move(value);

		changeAnimation(name, param);
	}

	void StateAnimator::insertParam(const std::string & name, std::any value)
	{
		parameters.insert({ name, std::move(value) });
	}

	void StateAnimator::tick()
	{
		if (penddingAnimation != animations.end())
		{
			if (penddingWaitPrevFin)
				if (!curAnimation->second->done())
					return;

			curAnimation = penddingAnimation;
			penddingAnimation = animations.end();
			return;
		}
	}

	const AnimateAble * StateAnimator::getCurAnimation() const
	{
		return curAnimation == animations.end() ? nullptr : curAnimation->second.get();
	}

	void StateAnimator::changeAnimation(const std::string & paramName, const std::any & param)
	{
		auto lowBound = transitions.lower_bound(paramName);
		auto upBound = transitions.upper_bound(paramName);

		for (auto itr = lowBound; itr != upBound; itr++)
		{
			if (itr->second.conditionAchived(param))
			{
				triggerTransition(itr->second);
				return;
			}
		}
	}

	void StateAnimator::triggerTransition(const TransitionInfo & tsInfo)
	{
		penddingAnimation = animations.find(tsInfo.getTransitionTo());
		penddingWaitPrevFin = tsInfo.isWaitUntilFinish();
		if (penddingAnimation == animations.end())
			throw std::runtime_error((boost::format("Animation \"%s\" does not found") % tsInfo.getTransitionTo()).str());
	}
}