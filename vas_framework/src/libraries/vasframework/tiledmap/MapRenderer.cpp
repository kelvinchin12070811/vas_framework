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
		if (renderer == nullptr) renderer = &Base::getInstance().Renderer();
		if (camera == nullptr) camera = &Camera::getInstance();

		sdl::Point tilePosition;
		for (tilePosition.y = 0; tilePosition.y < mapSize.y; tilePosition.y++)
		{
			for (tilePosition.x = 0; tilePosition.x < mapSize.x; tilePosition.x++)
			{
				auto rect = Camera::getInstance().getRectOnCamera(sdl::Rect(
					static_cast<int>(tilePosition.x), static_cast<int>(tilePosition.y),
					tileSize.x, tileSize.y
				) , staticOnCamera);
				if (Camera::getInstance().canSee(rect))
				{
					auto tile = layer->tileAt(tilePosition.x, tilePosition.y);
					if (tile != 0)
					{
						if (bundle->isAnimatedTile(tile))
						{
							auto frame = bundle->getAnimatiosData()[tile].getCurrentFrame();
							auto tileset = bundle->getTile(frame);
							tileset.second->drawTile(tileset.first, static_cast<Vector2>(tilePosition) * static_cast<Vector2>(tileSize), renderer, camera, staticOnCamera);
						}
						else
						{
							auto tileset = bundle->getTile(tile);
							tileset.second->drawTile(tileset.first, static_cast<Vector2>(tilePosition) * static_cast<Vector2>(tileSize), renderer, camera, staticOnCamera);
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