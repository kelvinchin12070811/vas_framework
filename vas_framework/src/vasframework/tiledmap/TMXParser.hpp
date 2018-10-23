#pragma once
#include <vector>
#include <memory>
#include <pugixml/pugixml.hpp>
#include "../VASConfig.hpp"
#include "container/MapProperties.hpp"
#include "container/Tileset.hpp"
#include "maplayers/TileLayer.hpp"
#include "maplayers/ObjectLayer.hpp"

namespace vas
{
	/** @addtogroup tile_codec
		  @{
	*/
	/** @brief Tiled TMX parser.
		  
		  TMXParser is a simple parser to read Tiled TMX map. TMXParser also represented as the map it self.
	*/
	class VAS_DECLSPEC TMXParser
	{ /** @} */
	public:
		TMXParser(); /**< Create empty parser. */
		TMXParser(const std::string& fileName); /**< Load from a file. @param fileName File to load. */
		~TMXParser();

		/** Load TMX map form a file.
			  @param fileName File to load.
		*/
		void load(const std::string& fileName = "");

		bool isEmpty() const; /**< Check if the map is empty. */

	public: // getters
		/** Get map layer data with index.
			  @param index Index of map layer.
			  @retval AbstractMapLayer* Selected layer's data, nullptr if failed.
		*/
		AbstractMapLayer* getDataAt(size_t index) const;
		/** Get map layer data with name.
			  @param name Name of map layer.
			  @retval AbstractMapLayer* Selected layer's data, nullptr if failed.
		*/
		AbstractMapLayer* getDataAt(const std::string& name) const;
		const std::vector<std::unique_ptr<AbstractMapLayer>>& getMapData() const;
		std::string getFileName() const;
		const MapProperties& getMapProperties() const;
		const std::vector<Tileset>& getRequireTilesets() const;
		sdl::Point getMapSize() const; /**< Get the size of the map. */

	private:
		void parse() const;
		void prase_mapProperties(pugi::xml_node node) const;
		void prase_tileset(pugi::xml_node node) const;
		void prase_tilelayer(pugi::xml_node node) const;
		void prase_objectlayer(pugi::xml_node node) const;
		Property prase_property(pugi::xml_node node) const;
		PropertyList propertiesPraser(pugi::xml_node node) const;
	private:
		/** [Read Only] Map data
				- __accessors__\n
					-# const std::vector<std::unique_ptr<AbstractMapLayer>>& getMapData() const
		*/
		mutable std::vector<std::unique_ptr<AbstractMapLayer>> mapData;
		/** [Read Only] Tilesets required to render the map.\n
				- __accesors__
					-# const std::vector<Tileset>& getRequireTilesets() const
		*/
		mutable std::vector<Tileset> tilesets;
		/** [Read Only] Properties of the map\n
				- __accessors__
					-# const MapProperties& getMapProperties() const
		*/
		mutable MapProperties mapProperties;
		/** [Read Only] File name of the loaded TMX map.\n
				- __accessors__
					-# std::string getFileName() const
		*/
		std::string fileName;
	};
}