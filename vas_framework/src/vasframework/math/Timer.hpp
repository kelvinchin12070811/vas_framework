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
		Timer();
		/** Create a timer with */
		explicit Timer(uint32_t interval);
		~Timer();

		boost::signals2::signal<void()>& TimedOutSignal();

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
		boost::signals2::signal<void()> timeOutSignal;
	};
}