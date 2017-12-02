#include "MapRenderer.hpp"
#include <algorithm>
#include "../../VASFramework/base/Camera.hpp"

namespace vas
{
	MapRenderer::MapRenderer(const std::shared_ptr<TMXParser>& praser, uint32_t drawlayer):
		praser(praser), drawLayer(drawlayer), tileAnimations(praser->getTileAnimations())
	{
		if (praser == nullptr) return;
		data = const_cast<LayerData*>(&praser->getMapData()[drawlayer]);
		tilesets = const_cast<std::vector<TilesetHolder>*>(&praser->getTilesets());
		mapWidth = praser->getMapWidth();
		mapHeight = praser->getMapHeight();
		tileWidth = praser->getTileWidth();
		tileHeight = praser->getTileHeight();
	}

	 MapRenderer::~MapRenderer()
	{
	}

	void MapRenderer::tick()
	{
		if (praser.expired()) return; //If map is destroyed then don't do any thing

#ifndef USE_MASTER_TILEANIAMTION_RENDERER
		for (auto itr = tileAnimations.begin(); itr != tileAnimations.end(); itr++)
		{
			if (std::find((*data)->begin(), (*data)->end(), itr->first) != (*data)->end())
				itr->second.tick();
		}
#endif // !USE_MASTER_TILEANIAMTION_RENDERER


		for (const auto& itr : *tilesets)
			if (itr.tileset != nullptr) itr.tileset->tick();
	}

	void MapRenderer::draw()
	{
		if (praser.expired()) return; //If map is destroyed then don't do any thing

		if (data->getOpacity() == 0) return; //If layer opacity is 0

		for (const auto& itr : *tilesets)
			if (itr.tileset) itr.tileset->setColour(vas::Colour(255, 255, 255, data->getOpacity()));

		for (uint32_t y = 0; y < mapHeight; y++)
			for (uint32_t x = 0; x < mapWidth; x++)
			{
				SDL_Rect position;
				position.x = (static_cast<int>(x) * tileWidth) - CameraAPI().getXOffset();
				position.y = (static_cast<int>(y) * tileHeight) - CameraAPI().getYOffset();
				position.w = tileWidth;
				position.h = tileHeight;
				if (!CameraAPI().canSee(position)) continue;

				uint32_t tileId = data->getTile(x, y, mapWidth);
				if (tileId == 0) continue; //If blank tile

				//tile animations
				tileAnimationPos = tileAnimations.find(tileId);
				if (tileAnimationPos != tileAnimations.end())
					tileId = tileAnimationPos->second.getCurrentFrame();

				selectedTilesets = std::find_if(tilesets->begin(), tilesets->end(), [&](const vas::TilesetHolder& value)->bool {
					return (tileId >= value.firstgid) && (tileId < value.firstgid + value.tilecount);
				});

				if (selectedTilesets == tilesets->end()) return;
				selectedTilesets->tileset->drawTileAt(tileId - selectedTilesets->firstgid, vas::Vector2(static_cast<float>(x * tileWidth), static_cast<float>(y * tileHeight)));
			}
	}
}