//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#if (__has_include(<pugixml/pugiconfig.hpp>) && __has_include(<zlib.h>)) || defined(DOXYGEN)
#include <map>
#include <unordered_map>
#include "Tileset.hpp"
#include "../../graphics/sprites/SpriteSheet.hpp"
#include "../../graphics/animation/AnimationController.hpp"

namespace vas
{
	/** @ingroup tile_codec
		  @{
	*/
	/** @brief The bundle ot tilesets that use by a map.

		  The TilesetsBundle contains tilesets that required to render the map.
	*/
	class VAS_DECLSPEC TilesetsBundle
	{ /**< @} */
	public:
		TilesetsBundle() = default; /**< Create empty bundle. */
		/** load from a raw data of tilesets.
			  @param tilesets Tilesets data.
			  @param w Width of the individual tile.
			  @param h Height of the individual tile.
		*/
		void load(const std::vector<Tileset>& tilesets, int w, int h);
		/** Return the sprite sheet and the index of the tile in that sprite sheet.
			  @param index index of the tile.
			  @retval std::pair<size_t, std::shared_ptr<SpriteSheet>> pair of index of the selected tile on the targeted spritesheets.
		*/
		std::pair<size_t, std::shared_ptr<SpriteSheet>> getTile(uint32_t index);
		/** Return the Tileset info of a tile.
			  @param index Index of the tile.
			  @return Tileset info of the tileset that contain the particular tile.
		*/
		const Tileset* getTileLocatedTilesets(uint32_t index);

		/** Determine if a tile is animated tile.
			  @param index Index of the tile.
			  @return true if it is animated tile.
		*/
		bool isAnimatedTile(uint32_t index);
		std::unordered_map<uint32_t, AnimationController>& getAnimatiosData(); /**< Get all the animated tiles data. */

		void tick(); /**< Update the animations of animated tiles. */
	private:
		std::map<uint32_t, std::pair<Tileset, std::shared_ptr<SpriteSheet>>, std::greater<uint32_t>> spriteData;
		std::unordered_map<uint32_t, AnimationController> animationsData;
		int w;
		int h;
	};
}
#endif // (__has_include(<pugixml/pugiconfig.hpp>) && __has_include(<zlib.h>)) || defined(DOXYGEN)
