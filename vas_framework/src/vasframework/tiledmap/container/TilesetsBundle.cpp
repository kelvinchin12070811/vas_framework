#include "TilesetsBundle.hpp"

namespace vas
{
	TilesetsBundle::TilesetsBundle()
	{
	}

	TilesetsBundle::~TilesetsBundle()
	{
	}

	void TilesetsBundle::load(const std::vector<Tileset>& tilesets, int w, int h)
	{
		this->w = w;
		this->h = h;
		for (auto& itr : tilesets)
		{
			spriteData.insert(std::make_pair(itr.firstGid,
				std::make_pair(
					itr,
					std::make_shared<SpriteSheet>(itr.source.name, sdl::Point(w, h))
				))
			);
			for (auto& itr2 : itr.tilesWithAnimation)
			{
				AnimationController controller(itr2.second.second, itr2.second.first);
				animationsData.insert(std::make_pair(itr2.first, std::move(controller)));
			}
		}
	}

	std::pair<size_t, std::shared_ptr<SpriteSheet>> TilesetsBundle::getTile(uint32_t index)
	{
		if (index == 0) return std::make_pair(0, nullptr);

		std::pair<size_t, std::shared_ptr<SpriteSheet>> selectedTile;
		auto result = spriteData.lower_bound(index);

		if (result == spriteData.end()) return std::make_pair(0, nullptr);
		selectedTile.first = index - result->second.first.firstGid;
		selectedTile.second = result->second.second;
		return selectedTile;
	}

	const Tileset * TilesetsBundle::getTileLocatedTilesets(uint32_t index)
	{
		if (index == 0) return nullptr;

		auto result = spriteData.lower_bound(index);
		if (result == spriteData.end()) return nullptr;
		return &result->second.first;
	}

	bool TilesetsBundle::isAnimatedTile(uint32_t index)
	{
		return animationsData.find(index) == animationsData.end() ? false : true;
	}

	std::unordered_map<uint32_t, AnimationController>& TilesetsBundle::getAnimatiosData()
	{
		return animationsData;
	}

	void TilesetsBundle::tick()
	{
		for (auto& itr : animationsData)
		{
			itr.second.tick();
		}
	}
}