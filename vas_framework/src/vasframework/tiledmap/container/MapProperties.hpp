#pragma once
#include "../../container/PropertyList.hpp"

namespace vas
{
	/** @addtogroup tile_codec
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