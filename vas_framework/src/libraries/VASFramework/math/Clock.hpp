#pragma once
#include <SDL.h>
#include "../config.hpp"

namespace vas
{
	class VAS_FRAMEWORK_DLLEXPORT Clock
	{
	public:
		Clock();
		Clock(const Clock& rhs);
		~Clock();

		uint32_t getTicks();
		uint32_t reset();
	private:
		uint32_t lastTicks = 0;
	};
}