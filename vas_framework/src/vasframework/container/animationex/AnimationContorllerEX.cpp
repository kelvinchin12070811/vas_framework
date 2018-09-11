#include "AnimationControllerEx.hpp"

namespace vas
{
	AdvAnimController::AdvAnimController()
	{
	}

	AdvAnimController::~AdvAnimController()
	{
	}

	void AdvAnimController::tick()
	{
		if (animationList.empty() || finished) return;

		if (curAnim == animationList.cend())
		{
			if (!loopAnim)
			{
				finished = true;
				return;
			}

			curAnim = animationList.cbegin();
		}
	}

	void AdvAnimController::restart()
	{
		if (animationList.empty()) return;
		curAnim = animationList.cbegin();
		finished = false;
	}

	const Animateable * AdvAnimController::currentAnim() const
	{
		if (animationList.empty())
			return nullptr;

		return curAnim->get();
	}

	size_t AdvAnimController::currentAnimIndex() const
	{
		if (animationList.empty())
			return 0;

		return std::distance(animationList.begin(), curAnim);
	}

	bool AdvAnimController::isFinished() const
	{
		return finished;
	}

	bool AdvAnimController::isLoopingAnim() const
	{
		return loopAnim;
	}

	void AdvAnimController::setLoopingAnim(bool value)
	{
		loopAnim = value;
	}
}