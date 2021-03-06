//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "Timer.hpp"
#include <exception>

namespace vas
{
	Timer::Timer(uint32_t interval):
		duration(interval), countingState(false)
	{
	}

	Timer::~Timer()
	{
		if (countingState)
			stop();
		TimedOut.disconnect_all_slots();
	}

	bool Timer::setInterval(std::chrono::milliseconds interval)
	{
		if (countingState) return false;
		duration = interval;
		return true;
	}

	void Timer::forceSetInterval(std::chrono::milliseconds interval)
	{
		duration = static_cast<std::chrono::milliseconds>(interval);
	}

	void Timer::start()
	{
		countingState = true;
		timerThread = std::thread{ std::bind(&Timer::threadRuner, this) };
	}

	void Timer::stop()
	{
		if (countingState == false) return;
		countingState = false;
		if (!timerThread.joinable())
			throw std::runtime_error{ "Timer thread is unjoinable." };
		timerThread.join();
	}

	bool Timer::started()
	{
		return countingState;
	}

	void Timer::threadRuner()
	{
		while (countingState)
		{
			using namespace std;
			using namespace chrono;
			std::this_thread::sleep_for(duration);
			TimedOut();
		}
	}
}