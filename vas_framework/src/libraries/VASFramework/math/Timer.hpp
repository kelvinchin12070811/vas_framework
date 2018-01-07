#pragma once
#include <cstdint>
#include "../config.hpp"

namespace vas
{
	class VAS_FRAMEWORK_DLLEXPORT Timer
	{
	public:
		Timer();
		explicit Timer(uint32_t tick, bool continues = true);
		Timer(const Timer&) = delete;
		~Timer();
		void tick();
		void start();
		void stop();
		void reset();
		void reset(uint32_t tick, bool continues = true);

		bool isTimedOut();
		uint32_t getTick();
		
		Timer& operator=(const Timer&) = delete;
	private:
		bool timedOut = false;
		bool counting = false;
		bool continues = true;
		bool firstCount = false;
		uint32_t tickCount = static_cast<uint32_t>(-1);
		uint32_t tickLimit = 0;
	};
	
	using Counter = Timer;
}