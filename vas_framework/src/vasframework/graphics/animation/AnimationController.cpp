//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "AnimationController.hpp"
#include "../../base/Base.hpp"

namespace vas
{
	AnimationController::AnimationController(const AnimationStrip & frames, std::chrono::milliseconds updateDelay)
	{
		load(frames, updateDelay);
	}

	void AnimationController::load(const AnimationStrip & frames, std::chrono::milliseconds updateDelay)
	{
		using namespace std::chrono_literals;
		this->frames = frames;
		this->frameIndexer.setAutoResetLimit(frames.size());
		std::chrono::milliseconds refreshRateHz{ 1000ms / Base::getInstance().getFPS() };
		this->frameUpdateTimer.setAutoResetLimit(static_cast<size_t>(updateDelay / refreshRateHz));
	}

	void AnimationController::tick()
	{
		frameUpdateTimer++;
		if (frameUpdateTimer == frameUpdateTimer.getMaxTick())
			frameIndexer++;
	}

	void AnimationController::reset()
	{
		frameIndexer.reset();
		frameUpdateTimer.reset();
	}

	void AnimationController::restart()
	{
		this->reset();
	}

	AnimationStrip::value_type AnimationController::getCurrentFrame()
	{
		return frames[frameIndexer];
	}
	size_t AnimationController::getCurrentFrameIndex()
	{
		return frameIndexer;
	}
}