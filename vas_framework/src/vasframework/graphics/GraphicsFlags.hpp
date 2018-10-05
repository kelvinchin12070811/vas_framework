#pragma once
#include <cstdint>

namespace vas
{
	/** @addtogroup graphics
		  @{
	*/
	/** Determin if the texture need to be cached or not.

		  Defined in: vasframework/graphics/GraphicsFlags.hpp, namespace: vas
	*/
	enum class BufferMode : uint8_t
	{
		buffered, /**< Cache textue with texture cache in TextureManager. */
		unbuffered /**< Bypas texture cache. */
	};
	/** @} */
}