#include "AnimationController.hpp"
#include "../../base/Base.hpp"

namespace vas
{
	AnimationController::AnimationController()
	{
	}

	AnimationController::AnimationController(const AnimationStrip & frames, std::chrono::milliseconds updateDelay)
	{
		load(frames, updateDelay);
	}

	AnimationController::~AnimationController()
	{
	}

	void AnimationController::load(const AnimationStrip & frames, std::chrono::milliseconds updateDelay)
	{
		using namespace std::chrono_literals;
		this->frames = frames;
		this->frameIndexer.setAutoResetLimit(frames.size());
		std::chrono::milliseconds refreshRateHz = 1000ms / Base::getInstance().getFPS();
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

	AnimationStrip::value_type AnimationController::getCurrentFrame()
	{
		return frames[frameIndexer];
	}
	size_t AnimationController::getCurrentFrameIndex()
	{
		return frameIndexer;
	}
}