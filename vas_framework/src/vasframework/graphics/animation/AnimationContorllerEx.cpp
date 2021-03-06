//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "AnimationControllerEx.hpp"

namespace vas
{
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
			if ((*curAnim)->done())
				curAnim++;
		}
		if (curAnim != animationList.end()) (*curAnim)->tick();
	}

	void AnimationControllerEx::restart()
	{
		if (animationList.empty()) return;
		curAnim->reset();
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
		if (curAnim != animationList.begin())
			curAnim = animationList.begin();
	}

	void AnimationControllerEx::insertAnimations(std::initializer_list<std::unique_ptr<AnimateAble>> animations)
	{
		for (auto& itr : animations)
			animationList.push_back(std::move(const_cast<std::unique_ptr<AnimateAble>&>(itr)));
		if (curAnim != animationList.begin())
			curAnim = animationList.begin();
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