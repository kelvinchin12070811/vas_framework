#pragma once
#include <chrono>
#include <memory>
#include <vector>
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

	public: //accessors
		bool isFinished() const;
		bool isLoopingAnim() const;

	public: //mutators
		void setLoopingAnim(bool value);

	private:
		bool finished{ false };
		bool loopAnim{ false };
		std::vector<std::unique_ptr<AnimateAble>> animationList;
		std::vector<std::unique_ptr<AnimateAble>>::const_iterator curAnim;
	};
}