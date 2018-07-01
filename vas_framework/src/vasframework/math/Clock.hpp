#pragma once
#include <chrono>
#include "../VASConfig.hpp"

namespace vas
{
	class VAS_DECLSPEC Clock
	{
	public:
		Clock();
		~Clock();

		std::chrono::nanoseconds reset();
		void justReset();
		std::chrono::nanoseconds currentTick();
	private:
		std::chrono::steady_clock::time_point startTime;
	};
}