//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "AnimationDelay.hpp"

namespace vas
{
	AnimationDelay::AnimationDelay(std::chrono::nanoseconds duration):
		duration(duration)
	{
	}

	void AnimationDelay::tick()
	{
		if (finished) finished = false;

		auto finishAnim = [](bool& finTag, std::chrono::steady_clock::time_point& tp)->void {
			finTag = true;
			tp = std::chrono::steady_clock::time_point{};
		};

		if (duration == duration.zero())
		{
			finishAnim(this->finished, startTime);
			return;
		}

		if (startTime.time_since_epoch() == std::chrono::nanoseconds::zero())
		{
			startTime = std::chrono::steady_clock::now();
		}
		
		if (auto elapsed = std::chrono::steady_clock::now() - startTime; elapsed >= duration)
		{
			finishAnim(this->finished, startTime);
		}
	}

	void AnimationDelay::setDuration(std::chrono::nanoseconds value)
	{
		duration = value;
	}

	std::chrono::nanoseconds AnimationDelay::getDuration() const
	{
		return duration;
	}
}