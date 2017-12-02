#pragma once
#include <string>
#include "../pugixml/pugixml.hpp"
#include "../VASFramework/containers/ByteArray.hpp"
#include "containeres/LayerData.hpp"
#include "containeres/TilesetHolder.h"
#include "containeres/Properties.hpp"
#include "containeres/Objectgroup.hpp"
#include "containeres/TileAnimation.hpp"

#define USE_MASTER_TILEANIAMTION_RENDERER

using namespace std::string_literals;

namespace vas
{
	class TMXPraser
	{
	public:
		TMXPraser();
		TMXPraser(const std::wstring& path);
		~TMXPraser();

		void initMap(const std::wstring& path = L""s);
		void praseMap();

		const std::vector<LayerData>& getMapData();
		const std::vector<TilesetHolder>& getTilesets();
		const Properties& getMapProperties();
		std::map<std::wstring, Objectgroup>& getObjectgroups();
		std::map<uint32_t, TileAnimation>& getTileAnimations();

		uint32_t getMapWidth();
		uint32_t getMapHeight();
		uint32_t getTileWidth();
		uint32_t getTileHeight();

		void tick(); //Update map tile animation
	private:
		void tilesetsPraser(pugi::xml_node_iterator& itr);
		void layerPraser(pugi::xml_node_iterator& itr);
		void propertiesPraser(pugi::xml_node_iterator& itr);
		void objectgroupPraser(pugi::xml_node_iterator& itr);
		void animationPraser(pugi::xml_object_range<pugi::xml_named_node_iterator>& object, uint32_t firstgid);
		
		std::wstring path;
		std::vector<LayerData> mapData;
		std::vector<TilesetHolder> tilesets;
		std::map<std::wstring, Objectgroup> objectgroups;
		std::map<uint32_t, TileAnimation> tileAnimations;
		pugi::xml_document document;
		pugi::xml_node map;
		Properties mapProperties;
		uint32_t tileWidth = 0;
		uint32_t tileHeight = 0;
		uint32_t mapWidth = 0;
		uint32_t mapHeight = 0;
	};
}