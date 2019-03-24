//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#if (__has_include(<pugixml/pugiconfig.hpp>) && __has_include(<zlib.h>)) || defined(DOXYGEN)
#include "../../container/PropertyList.hpp"

namespace vas
{
	/** @ingroup tile_codec
		  @{
	*/
	/** @brief Properties of the map

		  The basic information of the map.
	*/
	struct MapProperties
	{ /** @} */
		size_t mapWidth; /**< Width of the map. */
		size_t mapHeight; /**< Height of the map. */
		size_t tileWidth; /**< Width of the tiles. */
		size_t tileHeight; /**< Height of the tiles. */
		PropertyList customProperties; /**< Other custom properties of the map. */
	};
}
#endif // (__has_include(<pugixml/pugiconfig.hpp>) && __has_include(<zlib.h>)) || defined(DOXYGEN)
