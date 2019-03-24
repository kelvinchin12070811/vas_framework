//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <cstdint>

namespace vas
{
	/**
	 * @ingroup graphics
	 * @{
	 */
	/**
	 * Determin if the texture need to be cached or not.
	 * 
	 * Defined in: vasframework/graphics/GraphicsFlags.hpp, namespace: vas
	 */
	enum class BufferMode : uint8_t
	{
		buffered, /**< Cache textue with texture cache in TextureManager. */
		unbuffered /**< Bypas texture cache. */
	};
	/** @} */
}