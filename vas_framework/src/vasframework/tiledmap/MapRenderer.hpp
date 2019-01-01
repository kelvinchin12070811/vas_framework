//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#if (__has_include(<pugixml/pugiconfig.hpp>) && __has_include(<zlib.h>)) || defined(DOXYGEN)
#include <vector>
#include "maplayers/TileLayer.hpp"
#include "../graphics/sprites/SpriteSheet.hpp"
#include "container/TilesetsBundle.hpp"

namespace vas
{
	/** @addtogroup tile_codec
		  @{
	*/
	/** @brief Render one of the layer of map to the renderer.

		  The MapRenderer render one layer of the specified map to the screen.
	*/
	class VAS_DECLSPEC MapRenderer : public DrawAble
	{ /** @} */
	public:
		/** Create MapRenderer
			  @param layer Layer data to renderer.
			  @param mapSize Size of the map.
			  @param tileSize Size of the tile.
			  @param bundle Tilesets that use to render the map.
		*/
		MapRenderer(TileLayer* layer, const sdl::Point& mapSize, const sdl::Point& tileSize, const TilesetsBundle& bundle);

		void tick() override;
		void draw(sdl::Renderer* renderer = nullptr, Camera* camera = nullptr) override;

	public: //Setters
		void setStaticOnCamera(bool value);

	public: //Getters
		bool isStaticOnCamera();

	private:
		TileLayer * layer;
		TilesetsBundle* bundle;
		sdl::Point mapSize;
		sdl::Point tileSize;
		/** [Read & Write] Determine if this drawable object is static on camera.\n
				- __mutators__
					-# void setStaticOnCamera(bool value)
				- __accessors__
					-# bool isStaticOnCamera()
		*/
		bool staticOnCamera = false;
	};
}
#endif // (__has_include(<pugixml/pugiconfig.hpp>) && __has_include(<zlib.h>)) || defined(DOXYGEN)
