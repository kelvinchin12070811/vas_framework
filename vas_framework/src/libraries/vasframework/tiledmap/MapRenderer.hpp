#pragma once
#include <vector>
#include "maplayers/TileLayer.hpp"
#include "../graphics/sprites/SpriteSheet.hpp"
#include "container/TilesetsBundle.hpp"

namespace vas
{
	class VAS_DECLSPEC MapRenderer : IRendererAble
	{
	public:
		MapRenderer(TileLayer* layer, int mapWidth, int mapHeight, const TilesetsBundle& bundle);
		~MapRenderer();

		void tick() override;
		void draw() override;
	private:
		TileLayer* layer;
		TilesetsBundle bundle;
		int mapWidth{ 0 };
		int mapHeight{ 0 };
	};
}