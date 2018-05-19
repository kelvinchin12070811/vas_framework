#include "MapRenderer.hpp"
#include "../base/Base.hpp"
//#include "../"

namespace vas
{
	MapRenderer::MapRenderer(TileLayer* layer, int mapWidth, int mapHeight, const TilesetsBundle& bundle):
		layer(layer), mapWidth(mapWidth), mapHeight(mapHeight), bundle(bundle)
	{
	}

	MapRenderer::~MapRenderer()
	{
	}

	void MapRenderer::tick()
	{
		bundle.tick();
	}

	void MapRenderer::draw()
	{

	}
}