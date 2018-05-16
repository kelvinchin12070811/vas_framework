#pragma once
#include <vector>
#include "Tileset.hpp"
#include "../../graphics/sprites/SpriteSheet.hpp"

namespace vas
{
	class VAS_DECLSPEC TilesetsBundle
	{
	public:
		TilesetsBundle();
		~TilesetsBundle();
		void load(const std::vector<Tileset>& tilesets, int w, int h) const;
	private:
		mutable std::vector<std::pair<const Tileset&, std::shared_ptr<SpriteSheet>>> spriteData;
	};
}