#pragma once
#include <cstdint>

namespace vas
{
	enum class BufferMode : uint8_t
	{
		buffered,
		unbuffered
	};
}