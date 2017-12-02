#include "TileAnimation.hpp"

namespace vas
{
	TileAnimation::TileAnimation()
	{
	}

	TileAnimation::TileAnimation(const std::vector<uint32_t>& frameDurations, const std::vector<uint32_t>& frames) :
		frameDurations(frameDurations), frames(frames)
	{
		frameCounter.reset(frameDurations.size());
		frameCounter.start();
	}

	TileAnimation::TileAnimation(std::vector<uint32_t>&& frameDurations, std::vector<uint32_t>&& frames):
		frameDurations(std::move(frameDurations)), frames(std::move(frames))
	{
		frameCounter.reset(frameDurations.size());
		frameCounter.start();
	}

	TileAnimation::TileAnimation(TileAnimation && rhs) noexcept:
		frameDurations(std::move(rhs.frameDurations)), frames(std::move(rhs.frames)), updateClock(std::move(rhs.updateClock))
	{
		frameCounter.reset(frameDurations.size());
		frameCounter.start();
	}

	TileAnimation::~TileAnimation()
	{
		frameCounter.stop();
	}

	void TileAnimation::tick()
	{
		if (updateClock.getTicks() >= frameDurations[frameCounter.getTick()])
		{
			updateClock.reset();
			frameCounter.tick();
		}
	}

	uint32_t TileAnimation::getCurrentFrameIndex()
	{
		return frameCounter.getTick();
	}

	uint32_t TileAnimation::getCurrentFrame()
	{
		return frames[frameCounter.getTick()];
	}

	uint32_t TileAnimation::getTileId()
	{
		return frames[0];
	}
}