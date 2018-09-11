#include "AnimationControllerEx.hpp"

namespace vas
{
	AnimationControllerEx::AnimationControllerEx()
	{
	}

	AnimationControllerEx::~AnimationControllerEx()
	{
	}

	void AnimationControllerEx::tick()
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
		if ((*curAnim)->done()) curAnim++;
		(*curAnim)->tick();
	}

	void AnimationControllerEx::restart()
	{
		if (animationList.empty()) return;
		curAnim = animationList.cbegin();
		finished = false;
	}

	const AnimateAble * AnimationControllerEx::currentAnim() const
	{
		if (animationList.empty())
			return nullptr;

		return curAnim->get();
	}

	size_t AnimationControllerEx::currentAnimIndex() const
	{
		if (animationList.empty())
			return 0;

		return std::distance(animationList.begin(), curAnim);
	}

	bool AnimationControllerEx::isFinished() const
	{
		return finished;
	}

	bool AnimationControllerEx::isLoopingAnim() const
	{
		return loopAnim;
	}

	void AnimationControllerEx::setLoopingAnim(bool value)
	{
		loopAnim = value;
	}
}