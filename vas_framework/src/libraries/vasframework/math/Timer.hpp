#pragma once
#include <functional>
#include <boost/signals2.hpp>
#include <thread>
#include <chrono>
#include "../VASConfig.hpp"
#include "../container/Switch.hpp"

namespace vas
{
	class VAS_DECLSPEC Timer
	{
	public:
		Timer();
		explicit Timer(uint32_t interval);
		~Timer();

		boost::signals2::signal<void()>& TimedOutSignal();

		bool setInterval(std::chrono::milliseconds interval);
		//this function might be not safe because it try to set the interval while timer still going
		void forceSetInterval(std::chrono::milliseconds interval);

		void start();
		void stop();

		bool started();
	private:
		void threadRuner();

		Switch countingState;
		std::chrono::time_point<std::chrono::steady_clock> startTime;
		std::chrono::milliseconds duration{ 0 };
		std::thread timerThread;
		boost::signals2::signal<void()> timeOutSignal;
	};
}