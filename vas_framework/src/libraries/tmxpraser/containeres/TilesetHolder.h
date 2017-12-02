#pragma once
#include <memory>
#include "../../VASFramework/graphics/sprites/spritesheet/SpriteSheet.hpp"

namespace vas
{
	struct TilesetHolder
	{
		uint32_t firstgid;
		uint32_t tilecount;
		std::shared_ptr<SpriteSheet> tileset;
	};

	namespace tileset_holder
	{
		inline TilesetHolder create(uint32_t firstgid, uint32_t tilecount, const std::shared_ptr<SpriteSheet>& tileset)
		{
			return TilesetHolder{ firstgid, tilecount, tileset };
		}

		inline TilesetHolder create(uint32_t firstgid, uint32_t tilecount, std::shared_ptr<SpriteSheet>&& tileset)
		{
			return TilesetHolder{ firstgid, tilecount, std::move(tileset) };
		}
	}
}