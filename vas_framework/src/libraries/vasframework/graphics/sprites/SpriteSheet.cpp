#include "SpriteSheet.hpp"
#include "../../base/Base.hpp"

namespace vas
{
	SpriteSheet::SpriteSheet()
	{
	}

	SpriteSheet::SpriteSheet(const std::string & file, const sdl::Point & tileSize, const Vector2 & position,
		const sdl::Point & origin, BufferMode bfMode):
		Sprite(file, position, origin, bfMode), tileSize(tileSize)
	{
		this->destination.w = this->tileSize.x;
		this->destination.h = this->tileSize.y;

		tileSheetDimension = sdl::Point(source.w / tileSize.x, source.h / tileSize.y);
	}

	SpriteSheet::~SpriteSheet()
	{
	}

	void SpriteSheet::tick()
	{
		return;
	}

	void SpriteSheet::draw()
	{
		return;
	}

	void SpriteSheet::drawTile(size_t index, const Vector2 & position, const sdl::Point & origin, const vas::Angle & angle, sdl::Renderer::Flip flip)
	{
		auto renderer = Base::getInstance().Renderer();

		sdl::Point tilePos;
		tilePos.y = index / tileSheetDimension.x; //Calculate y pos of tile
		tilePos.x = index - (tilePos.y * tileSheetDimension.x); //Calculate x pos of tile scene y pos is getted
		tilePos *= tileSize; //Convert it back to pixel based position

		tileSource = sdl::Rect(tilePos.x, tilePos.y, tileSize.x, tileSize.y);
		tileDest = sdl::Rect(static_cast<int>(position.x), static_cast<int>(position.y), tileSize.x, tileSize.y);

		renderer.copyEx(this->texture, &tileSource, &tileDest, static_cast<double>(angle), origin, flip);
	}
}