#pragma once
#include <functional>
#include <boost/signals2.hpp>
#include <thread>
#include <chrono>
#include "../VASConfig.hpp"

namespace vas
{
	/** @addtogroup math
		  @{
	*/
	/** @brief Signal based timeout notifier.

		  The timer is a class that will notify other objects that observing it after a certain time.

		  @note Each of the Timer object will use one thread to start the timer.
	*/
	class VAS_DECLSPEC Timer
	{ /** @} */
	public:
		Timer() = default; /**< Create timer with no interval. */
		/** Create a timer with interval. */
		explicit Timer(uint32_t interval);
		Timer(const Timer&) = delete;
		Timer(Timer&&) = default;
		Timer& operator=(const Timer&) = delete;
		Timer& operator=(Timer&&) = default;
		~Timer();

		/** Set the interval of timer, the timer must stoped when this function is called.
			  @return true if success.
		*/
		bool setInterval(std::chrono::milliseconds interval);
		/** Force the timer to set the interval while the timer is started.
			  @warning This function might be not safe.
		*/
		void forceSetInterval(std::chrono::milliseconds interval);

		void start(); /**< Start the timer. */
		void stop(); /**< Stop the timer. */

		bool started(); /**< Check if the timer is started. */
	private:
		void threadRuner();

		bool countingState{ false };
		std::chrono::milliseconds duration{ 0 };
		std::thread timerThread;
	public:
		/** @name Signals */
		boost::signals2::signal<void()> timeOutSignal; /**< Signal fired when timer timed out. */
		/** @} */
	};
}