#pragma once
#include <cstdint>

namespace vas::sdl
{
	enum class BlendMode
	{
		/**< no blending
		dstRGBA = srcRGBA */
		none = 0x00000000,
		/**< alpha blending
		dstRGB = (srcRGB * srcA) + (dstRGB * (1-srcA))
		dstA = srcA + (dstA * (1-srcA)) */
		blend = 0x00000001,
		/**< additive blending
		dstRGB = (srcRGB * srcA) + dstRGB
		dstA = dstA */
		add = 0x00000002,
		/**< color modulate
		dstRGB = srcRGB * dstRGB
		dstA = dstA */
		mod = 0x00000004
	};
}