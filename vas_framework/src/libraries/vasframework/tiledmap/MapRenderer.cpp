#include "MapRenderer.hpp"

namespace vas
{
	MapRenderer::MapRenderer(const std::unique_ptr<TileLayer>& layer, int mapWidth, int mapHeight):
		layer(layer), mapWidth(mapWidth), mapHeight(mapHeight)
	{
	}

	MapRenderer::~MapRenderer()
	{
	}
	void MapRenderer::tick()
	{
	}
	void MapRenderer::draw()
	{
	}
}