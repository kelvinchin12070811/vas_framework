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
	class VAS_DECLSPEC TMXParser
	{
	public:
		TMXParser();
		TMXParser(const std::string& fileName);
		~TMXParser();

		void load(const std::string& fileName = "");

		bool isEmpty() const;

	public: // getters
		AbstractMapLayer* getDataAt(size_t index) const;
		AbstractMapLayer* getDataAt(const std::string& name) const;
		const std::vector<std::unique_ptr<AbstractMapLayer>>& getMapData() const;
		std::string getFileName() const;
		const MapProperties& getMapProperties() const;
		const std::vector<Tileset>& getRequireTilesets() const;

	private:
		void parse() const;
		void prase_mapProperties(pugi::xml_node& node) const;
		void prase_tileset(pugi::xml_node& node) const;
		void prase_tilelayer(pugi::xml_node& node) const;
		void prase_objectlayer(pugi::xml_node& node) const;
		Property prase_property(pugi::xml_node& node) const;
		PropertyList propertiesPraser(pugi::xml_node& node) const;
	private:
		mutable std::vector<std::unique_ptr<AbstractMapLayer>> mapData;
		mutable std::vector<Tileset> tilesets;
		mutable MapProperties mapProperties;
		std::string fileName;
	};
}