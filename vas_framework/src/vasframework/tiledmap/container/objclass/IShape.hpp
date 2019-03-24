//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once

#if (__has_include(<pugixml/pugiconfig.hpp>) && __has_include(<zlib.h>)) || defined(DOXYGEN)
namespace vas
{
	/** @ingroup tile_codec
		  @{
	*/
	/** @brief Basic shape object interface. */
	class IShape
	{ /** @} */
	public:
		IShape() = default;
		IShape(const IShape&) = default;
		IShape(IShape&&) = default;
		IShape& operator=(const IShape&) = default;
		IShape& operator=(IShape&&) = default;
		virtual ~IShape() = 0;
	};
	inline IShape::~IShape() = default;
}
#endif // (__has_include(<pugixml/pugiconfig.hpp>) && __has_include(<zlib.h>)) || defined(DOXYGEN)
