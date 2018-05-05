#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <zlib.h>
#include "TMXParser.hpp"
#include "maplayers/TileLayer.hpp"
#include "../sdlcore/math/Colour.hpp"
#include "../math/base64/base64.hpp"
#include "../container/BytesArray.hpp"

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

	std::string TMXParser::getFileName() const
	{
		return fileName;
	}

	const MapProperties & TMXParser::getMapProperties() const
	{
		return mapProperties;
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
				prase_properties(*itr);
			else if (static_cast<string>(itr->name()) == "tileset")
				prase_tileset(*itr);
			else if (static_cast<string>(itr->name()) == "layer")
				prase_tilelayer(*itr);
		}
	}

	void TMXParser::prase_properties(pugi::xml_node & node) const
	{
		using namespace std;
		if (!node.empty())
		{
			mapProperties.customProperties.reserve(std::distance(node.children().begin(), node.children().end()));
			auto propertyItr = node.children("property");
			for (auto& itr = propertyItr.begin(); itr != propertyItr.end(); itr++)
			{
				Property item;
				item.setName(itr->attribute("name").as_string());

				std::string type = itr->attribute("type").as_string();
				if (type == "string" || "file")
					item = static_cast<string>(itr->attribute("value").as_string());
				else if (type == "bool")
					item = itr->attribute("value").as_bool();
				else if (type == "float")
					item = itr->attribute("value").as_float();
				else if (type == "int")
					item = itr->attribute("value").as_int();
				else if (type == "color")
				{
					std::string colourValue = itr->attribute("value").as_string();
					item = sdl::Colour(
						boost::lexical_cast<uint8_t>(colourValue.substr(3, 2)),
						boost::lexical_cast<uint8_t>(colourValue.substr(5, 2)),
						boost::lexical_cast<uint8_t>(colourValue.substr(7, 2)),
						boost::lexical_cast<uint8_t>(colourValue.substr(1, 2))
					);
				}
				mapProperties.customProperties.push_back(std::move(item));
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
					uint32_t currentTileIndex = animationFramesData.begin()->attribute("tileid").as_uint();

					AnimationStrip tempStrip;
					tempStrip.reserve(std::distance(animationFramesData.begin(), animationFramesData.end()));
					for (auto& itr : animationFramesData)
						tempStrip.push_back(itr.attribute("tileid").as_uint());

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
		mapData.push_back(std::move(tempLayer));
	}
}