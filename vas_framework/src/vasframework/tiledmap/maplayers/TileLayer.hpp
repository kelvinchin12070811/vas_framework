//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#if (__has_include(<pugixml/pugiconfig.hpp>) && __has_include(<zlib.h>)) || defined(DOXYGEN)
#include <vector>
#include "AbstractMapLayer.hpp"

namespace vas
{
	/** @ingroup tile_codec
		  @{
	*/
	/** @brief The tiled map layer. */
	class VAS_DECLSPEC TileLayer : public AbstractMapLayer
	{ /** @} */
	public:
		TileLayer() = default; /**< Create new empty layer. */
		/** Create layer from raw data
			  @param data Map data of the layer.
			  @param width Layer width.
			  @param height Layer height.
			  @param opacity Layer opacity.
			  @param hidden Determine if the map is shown on the screen.
		*/
		TileLayer(const std::vector<uint32_t>& data, uint32_t width, uint32_t height, uint8_t opacity, bool hidden);
		/** Create layer from raw data
			  @param data rvalue of map data of the layer.
			  @param width Layer width.
			  @param height Layer height.
			  @param opacity Layer opacity.
			  @param hidden Determine if the map is shown on the screen.
		*/
		TileLayer(std::vector<uint32_t>&& data, uint32_t width, uint32_t height, uint8_t opacity, bool hidden);

		uint32_t tileAt(size_t index) const; /**< Get the tile at the given index. */
		uint32_t tileAt(int x, int y) const; /**< Get the tile at the given position. */

	public: // Getters
		const std::vector<uint32_t>& getTilesData() const;
		uint32_t getWidth() const;
		uint32_t getHeight() const;
		uint8_t getOpacity() const;
		bool isHidden() const;

	public: // Setters
		void setTilesData(const std::vector<uint32_t>& value);
		void setTilesData(std::vector<uint32_t>&& value);
		void setWidth(uint32_t value);
		void setHeight(uint32_t value);
		void setHidden(bool value);

	private:
		/** [Read & Write] Tiles data of the map.\n
				- __mutators__
					-# void setTilesData(const std::vector<uint32_t>& value)
					-# void setTilesData(std::vector<uint32_t>&& value)
				- __accessors__
					-# const std::vector<uint32_t>& getTilesData() const
		*/
		std::vector<uint32_t> tilesData;
		/** [Read & Write] Width of the layer.\n
				- __mutators__
					-# void setWidth(uint32_t value)
				- __accessors__
					-# uint32_t getWidth() const
		*/
		uint32_t width{ 0 };
		/** [Read & Write] Height of the layer.\n
				- __mutators__
					-# void setHeight(uint32_t value)
				- __accessors__
					-# uint32_t getHeight() const
		*/
		uint32_t height{ 0 };
		/** [Read Only] Opacity of the map.\n
				- __accessors__
					-# uint8_t getOpacity() const
			  @note The default map renderer will not process the map with this attribute. Implement your own class by extending
			  the MapRenderer class if you need to work with it.
		*/
		uint8_t opacity{ 255 };
		/** [Read & Write] Determine if the layer is hidden.\n
				- __mutators__
					-# void setHidden(bool value)
				- __accessors__
					-# bool isHidden() const
		*/
		bool hidden{ false };
	};
}
#endif // (__has_include(<pugixml/pugiconfig.hpp>) && __has_include(<zlib.h>)) || defined(DOXYGEN)
