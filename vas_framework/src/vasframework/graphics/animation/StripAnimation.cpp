//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "StripAnimation.hpp"

namespace vas
{
	void StripAnimation::insertFrame(size_t frame, SpriteSheet * spritesheet, Clock::DurationType stayTime)
	{
		if (spritesheet == nullptr)
			spritesheet = std::get<1>(this->back());

		if (stayTime == stayTime.zero())
			stayTime = std::get<2>(this->back());

		this->push_back({ frame, spritesheet, stayTime });
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
		return { std::get<0>(crFramePtr), std::get<1>(crFramePtr) };
	}
}