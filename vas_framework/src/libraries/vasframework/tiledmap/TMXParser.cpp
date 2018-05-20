#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <zlib.h>
#include "TMXParser.hpp"
#include "../sdlcore/math/Colour.hpp"
#include "../math/base64/base64.hpp"
#include "../container/BytesArray.hpp"
#include "container/objclass/AllShape.hpp"

namespace vas
{
	TMXParser::TMXParser()
	{
	}

	TMXParser::TMXParser(const std::string & fileName):
		fileName(fileName)
	{
		load();
	}

	TMXParser::~TMXParser()
	{
	}

	void TMXParser::load(const std::string & fileName)
	{
		if (!fileName.empty()) this->fileName = fileName;
		parse();
	}

	bool TMXParser::isEmpty() const
	{
		return mapData.empty();
	}

	AbstractMapLayer * TMXParser::getDataAt(size_t index) const
	{
		if (index < mapData.size())
		{
			return mapData[index].get();
		}
		return nullptr;
	}

	AbstractMapLayer * TMXParser::getDataAt(const std::string & name) const
	{
		auto result = std::find_if(mapData.begin(), mapData.end(), [&](std::unique_ptr<AbstractMapLayer>& itr)
		{
			return itr->getName() == name;
		});
		return result == mapData.end() ? nullptr : result->get();
	}

	const std::vector<std::unique_ptr<AbstractMapLayer>>& TMXParser::getMapData() const
	{
		return mapData;
	}

	std::string TMXParser::getFileName() const
	{
		return fileName;
	}

	const MapProperties & TMXParser::getMapProperties() const
	{
		return mapProperties;
	}

	const std::vector<Tileset> & TMXParser::getRequireTilesets() const
	{
		return tilesets;
	}
	
	void TMXParser::parse() const
	{
		using namespace std;
		pugi::xml_document mapDoc;
		{
			auto result = mapDoc.load_file(fileName.c_str());
			if (result.status != pugi::xml_parse_status::status_ok)
				throw std::runtime_error(result.description());
		}
		auto root = mapDoc.first_child();
		if (static_cast<string>(root.name()) != "map"s)
			throw std::runtime_error("Cannot parse \"" + fileName + "\". It might not a proper tmx map file");

		if (static_cast<string>(root.attribute("orientation").as_string()) != "orthogonal")
			throw std::runtime_error("This parser can only read orthogonal map");

		if (static_cast<string>(root.attribute("renderorder").as_string()) != "right-down")
			throw std::runtime_error("This parser can only read map that render from left to right, top to bottom");

		mapProperties.mapWidth = root.attribute("width").as_uint();
		mapProperties.mapHeight = root.attribute("height").as_uint();
		mapProperties.tileWidth = root.attribute("tilewidth").as_uint();
		mapProperties.tileHeight = root.attribute("tileheight").as_uint();

		for(auto itr = root.begin(); itr != root.end(); itr++)
		{
			if (static_cast<string>(itr->name()) == "properties")
				prase_mapProperties(*itr);
			else if (static_cast<string>(itr->name()) == "tileset")
				prase_tileset(*itr);
			else if (static_cast<string>(itr->name()) == "layer")
				prase_tilelayer(*itr);
			else if (static_cast<string>(itr->name()) == "objectgroup")
				prase_objectlayer(*itr);
		}
	}

	void TMXParser::prase_mapProperties(pugi::xml_node & node) const
	{
		using namespace std;
		if (!node.empty())
		{
			mapProperties.customProperties.reserve(std::distance(node.children().begin(), node.children().end()));
			auto propertyItr = node.children("property");
			for (auto& itr = propertyItr.begin(); itr != propertyItr.end(); itr++)
			{
				mapProperties.customProperties.push_back(prase_property(*itr));
			}
		}
	}

	void TMXParser::prase_tileset(pugi::xml_node & node) const
	{
		Tileset tmpTileset;
		tmpTileset.firstGid = node.attribute("firstgid").as_uint();
		tmpTileset.tileCount = node.attribute("tilecount").as_uint();
		tmpTileset.name = node.attribute("name").as_string();
		{
			auto imgSource = node.child("image");
			tmpTileset.source.name = imgSource.attribute("source").as_string();
			tmpTileset.source.width = imgSource.attribute("width").as_uint();
			tmpTileset.source.height = imgSource.attribute("height").as_uint();
		}
		if (!node.child("tile").empty())
		{
			auto tiles = node.children("tile");
			for (auto& itr : tiles)
			{
				auto tileAnimation = itr.child("animation");
				if (!tileAnimation.empty())
				{
					auto animationFramesData = tileAnimation.children("frame");
					uint32_t currentTileIndex = animationFramesData.begin()->attribute("tileid").as_uint() + tmpTileset.firstGid;

					AnimationStrip tempStrip;
					tempStrip.reserve(std::distance(animationFramesData.begin(), animationFramesData.end()));
					for (auto& itr : animationFramesData)
						tempStrip.push_back(itr.attribute("tileid").as_uint() + tmpTileset.firstGid);

					auto animationDetial = std::make_pair(
						std::chrono::milliseconds(animationFramesData.begin()->attribute("duration").as_llong()),
						std::move(tempStrip)
					);
					tmpTileset.tilesWithAnimation.insert(std::make_pair(currentTileIndex, std::move(animationDetial)));
				}
			}
		}
		tilesets.push_back(std::move(tmpTileset));
	}

	void TMXParser::prase_tilelayer(pugi::xml_node & node) const
	{
		using namespace std;
		string name = node.attribute("name").as_string();
		uint32_t width = node.attribute("width").as_uint();
		uint32_t height = node.attribute("height").as_uint();
		uint8_t opacity = static_cast<uint8_t>(node.attribute("opacity").as_float(1.0f) * std::numeric_limits<uint8_t>::max());
		bool hidden = node.attribute("visible").as_int(1) == 0;
		std::vector<uint32_t> layerDataExtr(width * height);

		auto data = node.child("data");
		if (!data.empty())
		{
			if (static_cast<string>(data.attribute("encoding").as_string()) != "base64")
				throw std::runtime_error("This parser currently only support map data that encode in base64.");
			if (static_cast<string>(data.attribute("compression").as_string()) != "zlib")
				throw std::runtime_error("The map data should be compressed using zlib!");

			//Parse data
			std::string layerData = data.text().as_string();
			boost::algorithm::trim(layerData);
			BytesArray layerDataDecode;
			layerDataDecode = base64::decode(layerData);

			uLongf targetSize = sizeof(uint32_t) * layerDataExtr.size();
			uncompress(reinterpret_cast<Bytef*>(layerDataExtr.data()), &targetSize, layerDataDecode.data(), layerDataDecode.size());
		}
		auto tempLayer = std::make_unique<TileLayer>(std::move(layerDataExtr), width, height, opacity, hidden);
		tempLayer->setName(name);
		tempLayer->setProperties(propertiesPraser(node.child("properties")));
		mapData.push_back(std::move(tempLayer));
	}

	void TMXParser::prase_objectlayer(pugi::xml_node & node) const
	{
		std::vector<ObjectData> tempObjList;
		auto tempLayer = std::make_unique<ObjectLayer>();
		auto objectsRaw = node.children("object");
		tempObjList.reserve(std::distance(objectsRaw.begin(), objectsRaw.end()));
		for (auto& itr : objectsRaw)
		{
			ObjectData tempDat;
			tempDat.name = itr.attribute("name").as_string();
			tempDat.type = itr.attribute("type").as_string();
			
			if (auto child = itr.child("ellipse"); child)
			{
				auto instance = std::make_unique<Ellipse>();
				instance->position = Vector2(itr.attribute("x").as_float(), itr.attribute("y").as_float());
				instance->width = itr.attribute("width").as_int();
				instance->height = itr.attribute("height").as_int();
				tempDat.instance = std::move(instance);
			}
			else if (child = itr.child("polyline"); child)
			{
				auto instance = std::make_unique<Polyline>();
				instance->position = Vector2(itr.attribute("x").as_float(), itr.attribute("y").as_float());
				std::string points = child.attribute("points").as_string();
				std::vector<std::string> pointsData;
				std::vector<Vector2> pointsPosition;
				boost::split(pointsData, points, [](char c) { return c == ' '; });
				
				for (auto& itr : pointsData)
				{
					std::vector<std::string> buffer;
					boost::split(buffer, itr, [](char c) { return c == ','; });
					pointsPosition.push_back(Vector2(boost::lexical_cast<float>(buffer[0]), boost::lexical_cast<float>(buffer[1])));
				}
				instance->line = std::move(pointsPosition);
				tempDat.instance = std::move(instance);
			}
			else if (child = itr.child("polygon"); child)
			{
				tempDat.instance = nullptr;
			}
			else
			{
				auto instance = std::make_unique<Rectangle>();
				instance->position = Vector2(itr.attribute("x").as_float(), itr.attribute("y").as_float());
				instance->width = itr.attribute("width").as_int();
				instance->height = itr.attribute("height").as_int();
				tempDat.instance = std::move(instance);
			}

			auto objectProperties = itr.child("properties");
			if (objectProperties)
				tempDat.properties = propertiesPraser(objectProperties);
			tempObjList.push_back(std::move(tempDat));
		}

		tempLayer->setName(node.attribute("name").as_string());
		tempLayer->setObjectList(std::move(tempObjList)); 
		tempLayer->setProperties(propertiesPraser(node.child("properties")));
		mapData.push_back(std::move(tempLayer));
	}

	Property TMXParser::prase_property(pugi::xml_node & node) const
	{
		using namespace std;
		Property item;
		item.setName(node.attribute("name").as_string());

		std::string type = node.attribute("type").as_string();
		if (type == "string" || "file")
			item = static_cast<string>(node.attribute("value").as_string());
		else if (type == "bool")
			item = node.attribute("value").as_bool();
		else if (type == "float")
			item = node.attribute("value").as_float();
		else if (type == "int")
			item = node.attribute("value").as_int();
		else if (type == "color")
		{
			std::string colourValue = node.attribute("value").as_string();
			item = sdl::Colour(
				boost::lexical_cast<uint8_t>(colourValue.substr(3, 2)),
				boost::lexical_cast<uint8_t>(colourValue.substr(5, 2)),
				boost::lexical_cast<uint8_t>(colourValue.substr(7, 2)),
				boost::lexical_cast<uint8_t>(colourValue.substr(1, 2))
			);
		}
		return item;
	}
	
	PropertyList TMXParser::propertiesPraser(pugi::xml_node & node) const
	{
		using namespace std;
		if (!node.empty())
		{
			PropertyList list;
			list.reserve(std::distance(node.children().begin(), node.children().end()));
			auto propertyItr = node.children("property");
			for (auto& itr = propertyItr.begin(); itr != propertyItr.end(); itr++)
			{
				list.push_back(prase_property(*itr));
			}
			return list;
		}
		return PropertyList();
	}
}