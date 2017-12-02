#include "TMXPraser.hpp"

#include <zlib.h>
#include <boost/algorithm/string.hpp>
#include "../VASFramework/util/TextTools.hpp"
#include "../VASFramework/util/CommonTools.hpp"
#include "../base64/base64.hpp"

namespace vas
{
	TMXPraser::TMXPraser()
	{
	}

	TMXPraser::TMXPraser(const std::wstring& path):
		path(path)
	{
		initMap();
		praseMap();
	}

	TMXPraser::~TMXPraser()
	{
	}

	void TMXPraser::initMap(const std::wstring & path)
	{
		if (!path.empty())
			if (this->path != path)
				this->path = path;

		auto result = this->document.load_file(this->path.c_str());
		if (result.status != pugi::status_ok)
			throw std::runtime_error(result.description());

		map = document.first_child();

		if (static_cast<std::wstring>(map.name()) != L"map"s)
			throw std::runtime_error(u8"invalid map file"s);
		if (static_cast<std::wstring>(map.attribute(L"version").as_string()) != L"1.0"s)
			throw std::runtime_error(u8"Unable to load tiled map, map version is not v1.0"s);
		if (static_cast<std::wstring>(map.attribute(L"orientation").as_string()) != L"orthogonal"s)
			throw std::runtime_error(u8"This praser only support orthogonal type of map"s);
		if (static_cast<std::wstring>(map.attribute(L"renderorder").as_string()) != L"right-down"s)
			throw std::runtime_error(u8"This praser only support right-down render order"s);
	}

	void TMXPraser::praseMap()
	{
		mapWidth = map.attribute(L"width").as_uint();
		mapHeight = map.attribute(L"height").as_uint();
		tileWidth = map.attribute(L"tilewidth").as_uint();
		tileHeight = map.attribute(L"tileheight").as_uint();

		for (auto mapContentsItr = map.begin(); mapContentsItr != map.end(); mapContentsItr++)
		{
			if (static_cast<std::wstring>(mapContentsItr->name()) == L"tileset"s) //Prase tilesets
				tilesetsPraser(mapContentsItr);
			else if (static_cast<std::wstring>(mapContentsItr->name()) == L"layer"s) //Prase layers
				layerPraser(mapContentsItr);
			else if (static_cast<std::wstring>(mapContentsItr->name()) == L"properties"s) //Prase properties
				propertiesPraser(mapContentsItr);
			else if (static_cast<std::wstring>(mapContentsItr->name()) == L"objectgroup")
				objectgroupPraser(mapContentsItr);
		}
	}

	const std::vector<LayerData>& TMXPraser::getMapData()
	{
		return mapData;
	}

	const std::vector<TilesetHolder>& TMXPraser::getTilesets()
	{
		return tilesets;
	}

	const Properties & TMXPraser::getMapProperties()
	{
		return mapProperties;
	}

	std::map<std::wstring, Objectgroup>& TMXPraser::getObjectgroups()
	{
		return objectgroups;
	}

	std::map<uint32_t, TileAnimation>& TMXPraser::getTileAnimations()
	{
		return tileAnimations;
	}

	uint32_t TMXPraser::getMapWidth()
	{
		return mapWidth;
	}

	uint32_t TMXPraser::getMapHeight()
	{
		return mapHeight;
	}

	uint32_t TMXPraser::getTileWidth()
	{
		return tileWidth;
	}

	uint32_t TMXPraser::getTileHeight()
	{
		return tileHeight;
	}

	void TMXPraser::tick()
	{
#ifdef USE_MASTER_TILEANIAMTION_RENDERER
		for (auto tileAnimationsItr = tileAnimations.begin(); tileAnimationsItr != tileAnimations.end(); tileAnimationsItr++) //Tick all tile animation
			tileAnimationsItr->second.tick();
#endif // USE_MASTER_TILEANIAMTION_RENDERER

	}

	void TMXPraser::tilesetsPraser(pugi::xml_node_iterator & itr)
	{
		TilesetHolder holder;
		holder.firstgid = itr->attribute(L"firstgid").as_uint();
		holder.tilecount = itr->attribute(L"tilecount").as_uint();

		auto image = itr->child(L"image");
		std::wstring imageSource = image.attribute(L"source").as_string();
		imageSource = L"assets/" + (imageSource.find(L"../"s) != std::wstring::npos ? imageSource.substr(3) : imageSource);
		holder.tileset = std::make_shared<vas::SpriteSheet>(imageSource, vas::Vector2(), tileWidth, tileHeight);
		tilesets.push_back(std::move(holder));

		if (!itr->child(L"tile").child(L"animation").empty()) //Prase animation if tileset content animations
		{
			auto tiles = itr->children(L"tile");
			animationPraser(tiles, tilesets.back().firstgid);
		}
	}

	void TMXPraser::layerPraser(pugi::xml_node_iterator & itr)
	{
		if (itr->attribute(L"visible").as_int(1) == 0) return; //skip if layer is not visible

		auto child = itr->child(L"data");
		if (static_cast<std::wstring>(child.attribute(L"compression").as_string()) != L"zlib"s) return; //Skip if not zlib compression

		std::string rawData = str_cast<std::string>(child.text().as_string());
		ByteArray bufferBeforeUncompress, bufferAfterUncompress(sizeof(uint32_t) * mapWidth * mapHeight);

		boost::algorithm::trim(rawData); //Cleanup data so it contents only base64 charater

		bufferBeforeUncompress = vas::base64::decode(rawData);

		uLongf destLength = static_cast<uLongf>(bufferAfterUncompress.size());
		uncompress(bufferAfterUncompress.data(), &destLength, bufferBeforeUncompress.data(), bufferBeforeUncompress.size());
		LayerData data;
		data->resize(mapWidth * mapHeight);
		memcpy(data->data(), bufferAfterUncompress.data(), bufferAfterUncompress.size());
		uint8_t opacity = static_cast<uint8_t>(itr->attribute(L"opacity").as_float(1.0f) * 255);
		data.setOpacity(opacity);
		mapData.push_back(std::move(data));
	}

	void TMXPraser::propertiesPraser(pugi::xml_node_iterator & itr)
	{
		for (auto propertyNode = itr->begin(); propertyNode != itr->end(); propertyNode++)
			mapProperties.push_back(Property(propertyNode->attribute(L"name").as_string(), static_cast<std::wstring>(propertyNode->attribute(L"value").as_string())));
	}

	void TMXPraser::objectgroupPraser(pugi::xml_node_iterator & itr)
	{
		Objectgroup objectgroup;
		for (auto objItr = itr->begin(); objItr != itr->end(); objItr++)
		{
			if (static_cast<std::wstring>(objItr->name()) == L"object")
			{
				pugi::xml_node objectNode = *objItr;
				Object object;
				object.id = objectNode.attribute(L"id").as_uint();
				object.name = objectNode.attribute(L"name").as_string();
				object.type = objectNode.attribute(L"type").as_string();
				object.visible = objectNode.attribute(L"visible").as_bool(true);
				object.position = Vector2(objectNode.attribute(L"x").as_float(), objectNode.attribute(L"y").as_float());
				object.width = objectNode.attribute(L"width").as_uint();
				object.height = objectNode.attribute(L"heighi").as_uint();
				object.rotation = static_cast<Angle>(objectNode.attribute(L"rotation").as_float());
				
				auto propertiesNode = objItr->child(L"properties");
				if (!propertiesNode.empty())
				{
					for (auto propertyItr = propertiesNode.begin(); propertyItr != propertiesNode.end(); propertyItr++)
						object.customProperties.push_back(Property(propertyItr->attribute(L"name").as_string(), static_cast<std::wstring>(propertyItr->attribute(L"value").as_string())));
				}
				objectgroup.push_back(std::move(object));
			}
		}

		std::wstring objgName = itr->attribute(L"name").as_string();
		if (objectgroups.find(objgName) != objectgroups.end())
			throw (std::runtime_error("duplicate object group consits in the map: "s + str_cast<std::string>(objgName)));

		objectgroups[objgName] = std::move(objectgroup);
	}

	void TMXPraser::animationPraser(pugi::xml_object_range<pugi::xml_named_node_iterator>& object, uint32_t firstgid)
	{
		for (auto itr = object.begin(); itr != object.end(); itr++)
		{
			if (!itr->child(L"animation").empty())
			{
				uint32_t tileId = itr->attribute(L"id").as_uint() + firstgid;
				auto framesNode = itr->child(L"animation").children(L"frame");
				
				size_t frameCount = std::distance(framesNode.begin(), framesNode.end());
				std::vector<uint32_t> frameduration;
				std::vector<uint32_t> frames;
				frameduration.reserve(frameCount);
				frames.reserve(frameCount);

				for (auto frameItr = framesNode.begin(); frameItr != framesNode.end(); frameItr++)
				{
					frames.push_back(frameItr->attribute(L"tileid").as_uint() + firstgid);
					frameduration.push_back(frameItr->attribute(L"duration").as_uint());
				}

				TileAnimation animation(std::move(frameduration), std::move(frames));
				tileAnimations.insert(std::make_pair(tileId, std::move(animation)));
			}
		}
	}
}