#pragma once
#include <string>
#include <map>
#include <chrono>
#include "../../container/AnimationStrip.hpp"

namespace vas
{
	struct TilesetSource
	{
		std::string name;
		uint32_t width;
		uint32_t height;
	};

	struct Tileset
	{
		std::string name;
		uint32_t firstGid;
		uint32_t tileCount;
		TilesetSource source;
		std::map<uint32_t, std::pair<std::chrono::milliseconds, AnimationStrip>> tilesWithAnimation;
	};
}