#pragma once
#include <cstdint>

namespace vas::sdl
{
	/** @addtogroup sdl_basic
		  @{
	*/
	/** @brief Blend modes of sdl::Textuer.
	*/
	enum class BlendMode
	{ /** @} */
		/** no blending\n
		dstRGBA = srcRGBA */
		none = 0x00000000,
		/** alpha blending\n
		dstRGB = (srcRGB * srcA) + (dstRGB * (1-srcA))\n
		dstA = srcA + (dstA * (1-srcA)) */
		blend = 0x00000001,
		/** additive blending\n
		dstRGB = (srcRGB * srcA) + dstRGB\n
		dstA = dstA */
		add = 0x00000002,
		/** color modulate\n
		dstRGB = srcRGB * dstRGB\n
		dstA = dstA */
		mod = 0x00000004
	};
}