#pragma once
#include <string>
#include <map>
#include <chrono>
#include "../../graphics/animation/AnimationStrip.hpp"

namespace vas
{
	/** @addtogroup tile_codec
		  @{
	*/
	/** @brief Tileset source information.
		  
		  The information of tileset's file.
	*/
	struct TilesetSource
	{
		std::string name; /**< File name of the tileset sheet. */
		uint32_t width; /**< width of the tileset. */
		uint32_t height; /**< height of the tileset. */
	};

	/** @brief Tileset metadatas.
		  
		  The information about the tileset.
	*/
	struct Tileset
	{
		std::string name; /**< Name of the tileset. */
		uint32_t firstGid; /**< First id of the tileset, last tile id + 1. */
		uint32_t tileCount; /**< Number of tiles contained. */
		TilesetSource source; /**< Source file information. */
		std::map<uint32_t, std::pair<std::chrono::milliseconds, AnimationStrip>> tilesWithAnimation; /**< Animation datas, tiles that contain animations. */
	};
	/** @} */
}