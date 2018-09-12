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

		if (curAnim == animationList.end())
		{
			if (!loopAnim)
			{
				finished = true;
				return;
			}
			curAnim = animationList.begin();
		}
		else
		{
			if ((*curAnim)->done()) curAnim++;
		}
		if (curAnim != animationList.end()) (*curAnim)->tick();
	}

	void AnimationControllerEx::restart()
	{
		if (animationList.empty()) return;
		curAnim = animationList.begin();
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

		return std::distance(const_cast<AnimationControllerEx*>(this)->animationList.begin(), curAnim);
	}

	void AnimationControllerEx::insertAnimation(std::unique_ptr<AnimateAble> animation)
	{
		animationList.push_back(std::move(animation));
		if (animationList.size() == 1) curAnim = animationList.begin();
	}

	void AnimationControllerEx::removeAnimation()
	{
		animationList.pop_back();
	}

	void AnimationControllerEx::clear()
	{
		animationList.clear();
	}

	bool AnimationControllerEx::isEmpty() const
	{
		return animationList.empty();
	}

	size_t AnimationControllerEx::size() const
	{
		return animationList.size();
	}

	bool AnimationControllerEx::isFinished() const
	{
		return finished;
	}

	bool AnimationControllerEx::isLoopingAnim() const
	{
		return loopAnim;
	}

	std::list<std::unique_ptr<AnimateAble>>& AnimationControllerEx::getAnimationList()
	{
		return const_cast<std::list<std::unique_ptr<AnimateAble>>&>(
			const_cast<const AnimationControllerEx*>(this)->getAnimationList());
	}

	const std::list<std::unique_ptr<AnimateAble>>& AnimationControllerEx::getAnimationList() const
	{
		return animationList;
	}

	void AnimationControllerEx::setLoopingAnim(bool value)
	{
		loopAnim = value;
	}
}