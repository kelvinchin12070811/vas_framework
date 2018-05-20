#pragma once
#include <vector>
#include "Tileset.hpp"
#include "../../graphics/sprites/SpriteSheet.hpp"
#include "../../container/AnimationController.hpp"

namespace vas
{
	class VAS_DECLSPEC TilesetsBundle
	{
	public:
		TilesetsBundle();
		~TilesetsBundle();
		void load(const std::vector<Tileset>& tilesets, int w, int h);
		//return the sprite sheet and the index of the tile in that sprite sheet
		std::pair<size_t, std::shared_ptr<SpriteSheet>> getTile(uint32_t index);
		Tileset* getTileLocatedTilesets(uint32_t index);
		
		bool isAnimatedTile(uint32_t index);
		std::map<uint32_t, AnimationController>& getAnimatiosData();

		void tick();
	private:
		std::vector<std::pair<Tileset, std::shared_ptr<SpriteSheet>>> spriteData;
		std::map<uint32_t, AnimationController> animationsData;
		int w;
		int h;
	};
}