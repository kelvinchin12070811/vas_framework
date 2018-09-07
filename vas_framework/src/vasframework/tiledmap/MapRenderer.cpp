#include "MapRenderer.hpp"
#include "../base/Base.hpp"
#include "../graphics/Camera.hpp"

namespace vas
{
	MapRenderer::MapRenderer(TileLayer* layer, const sdl::Point& mapSize, const sdl::Point& tileSize, const TilesetsBundle& bundle):
		layer(layer), mapSize(mapSize), tileSize(tileSize), bundle(const_cast<TilesetsBundle*>(&bundle))
	{
	}

	MapRenderer::~MapRenderer()
	{
	}

	void MapRenderer::tick()
	{
		//bundle->tick();
	}

	void MapRenderer::draw(sdl::Renderer* renderer, Camera* camera)
	{
		if (layer == nullptr) return;
		if (renderer == nullptr) renderer = &Base::getInstance().getRenderer();
		if (camera == nullptr) camera = &Camera::getInstance();

		sdl::Point tilePosition;
		for (tilePosition.y = 0; tilePosition.y < mapSize.y; tilePosition.y++)
		{
			for (tilePosition.x = 0; tilePosition.x < mapSize.x; tilePosition.x++)
			{
				Vector2 targetPos = Vector2(tilePosition) * Vector2(tileSize);
				if (camera->canSee(targetPos, tileSize))
				{
					auto tile = layer->tileAt(tilePosition.x, tilePosition.y);
					if (tile != 0)
					{
						if (auto targetTile = bundle->getAnimatiosData().find(tile); targetTile != bundle->getAnimatiosData().end())
						{
							auto tileset = bundle->getTile(targetTile->second.getCurrentFrame());
							tileset.second->drawTile(tileset.first, targetPos, renderer, camera, staticOnCamera);
						}
						else
						{
							auto tileset = bundle->getTile(tile);
							tileset.second->drawTile(tileset.first, targetPos, renderer, camera, staticOnCamera);
						}
					}
				}
			}
		}
	}

	void MapRenderer::setStaticOnCamera(bool value)
	{
		staticOnCamera = value;
	}

	bool MapRenderer::isStaticOnCamera()
	{
		return staticOnCamera;
	}
}