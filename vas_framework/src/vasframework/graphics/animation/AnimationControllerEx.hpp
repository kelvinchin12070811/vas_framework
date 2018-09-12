#pragma once
#include <chrono>
#include <memory>
#include <list>
#include "Animateable.hpp"
#include "AutoControllable.hpp"
#include "../../VASConfig.hpp"

namespace vas
{
	class VAS_DECLSPEC AnimationControllerEx : public AutoControllable
	{
	public:
		AnimationControllerEx();
		~AnimationControllerEx();

		void tick() override;
		void restart();

		const AnimateAble* currentAnim() const;
		size_t currentAnimIndex() const;

		void insertAnimation(std::unique_ptr<AnimateAble> animation);
		void removeAnimation();
		void clear();

		bool isEmpty() const;
		size_t size() const;

	public: //accessors
		bool isFinished() const;
		bool isLoopingAnim() const;
		std::list<std::unique_ptr<AnimateAble>>& getAnimationList();
		const std::list<std::unique_ptr<AnimateAble>>& getAnimationList() const;

	public: //mutators
		void setLoopingAnim(bool value);

	private:
		bool finished{ false };
		bool loopAnim{ false };
		std::list<std::unique_ptr<AnimateAble>> animationList;
		std::list<std::unique_ptr<AnimateAble>>::iterator curAnim;
	};
}