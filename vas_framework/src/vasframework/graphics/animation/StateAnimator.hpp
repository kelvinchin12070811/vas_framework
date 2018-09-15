#pragma once
#include <any>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "AnimateAble.hpp"
#include "AutoControllable.hpp"
#include "TransitionInfo.hpp"

namespace vas
{
	class VAS_DECLSPEC StateAnimator : public AutoControllable
	{
	public:
		StateAnimator();
		~StateAnimator();

		void insertTransition(TransitionInfo info, const std::string& mapedParam = "");

		void triggerParam(const std::string& name);
		void setParamValue(const std::string& name, std::any value);
		void insertParam(const std::string& name, std::any value);

		void tick() override;

		const AnimateAble* getCurAnimation() const;
	private:
		void changeAnimation(const std::string& paramName, const std::any& param);
		void triggerTransition(const TransitionInfo& tsInfo);
	private:
		std::map<std::string, std::unique_ptr<AnimateAble>> animations;
		std::map<std::string, std::any> parameters;
		std::multimap<std::string, TransitionInfo>transitions;
		std::map<std::string, std::unique_ptr<AnimateAble>>::iterator curAnimation;
		std::map<std::string, std::unique_ptr<AnimateAble>>::iterator penddingAnimation;
		bool penddingWaitPrevFin{ false };
	};
}