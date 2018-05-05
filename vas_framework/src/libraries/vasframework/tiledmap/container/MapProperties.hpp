#pragma once
#include "../../container/PropertyList.hpp"

namespace vas
{
	struct MapProperties
	{
		size_t mapWidth;
		size_t mapHeight;
		size_t tileWidth;
		size_t tileHeight;
		PropertyList customProperties;
	};
}