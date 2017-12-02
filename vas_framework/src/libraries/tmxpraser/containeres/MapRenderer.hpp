#pragma once
#include <memory>
#include "../TMXPraser.hpp"
#include "../../VASFramework/graphics/irender_able/iRenderAble.hpp"

namespace vas
{
	class MapRenderer : public iRenderAble
	{
	public:
		MapRenderer(const std::shared_ptr<TMXPraser>& praser, uint32_t drawlayer);
		~MapRenderer();

		void tick() override;
		void draw() override;
	private:
		std::weak_ptr<TMXPraser> praser;
		uint32_t drawLayer = 0;
		LayerData* data = nullptr;
		uint32_t mapWidth = 0;
		uint32_t mapHeight = 0;
		uint32_t tileWidth = 0;
		uint32_t tileHeight = 0;
		std::vector<TilesetHolder>* tilesets = nullptr;
		std::vector<TilesetHolder>::iterator selectedTilesets;
		std::map<uint32_t, TileAnimation>& tileAnimations;
		std::map<uint32_t, TileAnimation>::iterator tileAnimationPos;
	};
}