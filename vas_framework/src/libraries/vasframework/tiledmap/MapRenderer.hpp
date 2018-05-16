#pragma once
#include "TMXParser.hpp"
#include "../graphics/sprites/SpriteSheet.hpp"

namespace vas
{
	class VAS_DECLSPEC MapRenderer : IRendererAble
	{
	public:
		MapRenderer(const std::unique_ptr<TileLayer>& layer, int mapWidth, int mapHeight);
		~MapRenderer();

		void tick() override;
		void draw() override;
	private:
		const std::unique_ptr<TileLayer>& layer;
		int mapWidth{ 0 };
		int mapHeight{ 0 };
	};
}