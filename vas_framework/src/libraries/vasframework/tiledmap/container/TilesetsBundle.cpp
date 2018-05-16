#include <filesystem>
#include "TilesetsBundle.hpp"

namespace vas
{
	TilesetsBundle::TilesetsBundle()
	{
	}

	TilesetsBundle::~TilesetsBundle()
	{
	}

	void TilesetsBundle::load(const std::vector<Tileset>& tilesets, int w, int h) const
	{
		using namespace std::experimental;
		spriteData.reserve(tilesets.size());
		for (auto& itr : tilesets)
		{
			filesystem::path(itr.source.name);
			auto sprite = std::make_shared<SpriteSheet>(itr.source.name, sdl::Point(w, h));
		}
	}
}