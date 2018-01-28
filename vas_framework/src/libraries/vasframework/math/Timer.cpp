#include "Timer.hpp"
#include <exception>

namespace vas
{
	Timer::Timer()
	{
	}
	Timer::Timer(uint32_t interval):
		duration(interval), countingState(off)
	{
	}

	Timer::~Timer()
	{
		if (countingState.is(on))
			stop();
		timeOutSignal.disconnect_all_slots();
	}

	boost::signals2::signal<void()>& Timer::TimedOutSignal()
	{
		return timeOutSignal;
	}

	bool Timer::setInterval(std::chrono::milliseconds interval)
	{
		if (countingState.is(on)) return false;
		duration = interval;
		return true;
	}

	void Timer::forceSetInterval(std::chrono::milliseconds interval)
	{
		duration = static_cast<std::chrono::milliseconds>(interval);
	}

	void Timer::start()
	{
		countingState(on);
		startTime = std::chrono::steady_clock::now();
		timerThread = std::thread(std::bind(&Timer::threadRuner, this));
	}

	void Timer::stop()
	{
		countingState(off);
		if (!timerThread.joinable())
			throw std::runtime_error("Timer thread is unjoinable.");
		timerThread.join();
	}

	bool Timer::started()
	{
		return countingState.is(on);
	}

	void Timer::threadRuner()
	{
		while (countingState.is(on))
		{
			using namespace std;
			using namespace chrono;
			auto currentTime = steady_clock::now();
			auto totalDuration = duration_cast<milliseconds>(currentTime - startTime);
			if (totalDuration == this->duration)
			{
				timeOutSignal();
				startTime = steady_clock::now();
			}
		}
	}
}