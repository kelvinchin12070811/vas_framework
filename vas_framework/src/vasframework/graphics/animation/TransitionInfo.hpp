#pragma once
#include <any>
#include <functional>
#include <string>
#include "../../VASConfig.hpp"

namespace vas
{
	class VAS_DECLSPEC TransitionInfo
	{
	public:
		TransitionInfo(const std::string& to, std::function<bool(const std::any&)> condition, bool waitFinish = false);
		~TransitionInfo();

		bool conditionAchived(const std::any& param) const;
		bool isWaitUntilFinish() const;
		const std::string& getTransitionTo() const;
	private:
		bool waitFinish;
		std::string to;
		std::function<bool(const std::any&)> condition;
	};
}