#include "StripAnimation.hpp"

namespace vas
{
	StripAnimation::StripAnimation()
	{
	}

	StripAnimation::~StripAnimation()
	{
	}

	void StripAnimation::insertFrame(size_t frame, SpriteSheet * spritesheet, Clock::DurationType stayTime)
	{
		if (spritesheet == nullptr)
			spritesheet = std::get<1>(this->back());

		if (stayTime == stayTime.zero())
			stayTime = std::get<2>(this->back());

		this->push_back(std::make_tuple(frame, spritesheet, stayTime));
	}

	void StripAnimation::tick()
	{
		if (this->empty()) //return and mark as not started if frames is empty
		{
			if (updateClock != nullptr) updateClock = nullptr;
			return;
		}

		if (finished) finished = false;

		if (updateClock == nullptr) //Check if first start
		{
			updateClock = std::make_unique<Clock>();
			currentFrame = this->begin();
		}

		auto now = updateClock->currentTick();
		if (now >= std::get<2>(*currentFrame))
		{
			updateClock->justReset();
			currentFrame++;
			if (currentFrame == this->end())
			{
				finished = true;
				currentFrame = this->begin();
			}
		}
	}

	std::pair<size_t, const SpriteSheet*> StripAnimation::getCurrentFrame() const
	{
		auto crFramePtr = *currentFrame;
		return std::make_pair(std::get<0>(crFramePtr), std::get<1>(crFramePtr));
	}
}