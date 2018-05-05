#pragma once
#include <vector>
#include <memory>
#include <pugixml/pugixml.hpp>
#include "../VASConfig.hpp"
#include "maplayers/AbstractMapLayer.hpp"
#include "container/MapProperties.hpp"
#include "container/Tileset.hpp"

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
		std::string getFileName() const;
		const MapProperties& getMapProperties() const;

	private:
		void parse() const;
		void prase_properties(pugi::xml_node& node) const;
		void prase_tileset(pugi::xml_node& node) const;
		void prase_tilelayer(pugi::xml_node& node) const;

	private:
		mutable std::vector<std::unique_ptr<AbstractMapLayer>> mapData;
		mutable std::vector<Tileset> tilesets;
		mutable MapProperties mapProperties;
		std::string fileName;
	};
}