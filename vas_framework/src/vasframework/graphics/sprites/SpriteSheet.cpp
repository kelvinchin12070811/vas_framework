//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "SpriteSheet.hpp"
#include "../../base/Base.hpp"
#include "../Camera.hpp"

namespace vas
{
	SpriteSheet::SpriteSheet(const std::string & file, const sdl::Point & tileSize, const Vector2 & position,
		const sdl::Point & origin, BufferMode bfMode):
		Sprite(file, position, origin, bfMode), tileSize(tileSize)
	{
		this->destination.w = this->tileSize.x;
		this->destination.h = this->tileSize.y;

		tileSheetDimension = sdl::Point(source.w / tileSize.x, source.h / tileSize.y);
	}

	void SpriteSheet::tick()
	{
		return;
	}

	void SpriteSheet::draw(sdl::Renderer* renderer, Camera* camera)
	{
		return;
	}

	void SpriteSheet::drawTile(size_t index, const Vector2 & position, sdl::Renderer* renderer, Camera* camera, bool staticOnCamera, const sdl::Point & origin, const vas::Angle & angle, sdl::Renderer::Flip flip)
	{
		sdl::Renderer rendererHolder{ (renderer == nullptr) ? Base::getInstance().getRenderer() : *renderer };
		if (camera == nullptr) camera = &Camera::getInstance();

		sdl::Point tilePos;
		tilePos.y = index / tileSheetDimension.x; //Calculate y pos of tile
		tilePos.x = index - (tilePos.y * tileSheetDimension.x); //Calculate x pos of tile scene y pos is getted
		tilePos *= tileSize; //Convert it back to pixel based position

		tileSource = sdl::Rect{ tilePos.x, tilePos.y, tileSize.x, tileSize.y };
		tileDest = sdl::Rect{ static_cast<int>(position.x), static_cast<int>(position.y), tileSize.x, tileSize.y };

		if (staticOnCamera)
		{
			rendererHolder.copyEx(this->texture, &tileSource, &tileDest, static_cast<double>(angle), origin, flip);
		}
		else
		{
			tileDest = camera->getRectOnCamera(tileDest);
			rendererHolder.copyEx(this->texture, &tileSource, &tileDest, static_cast<double>(angle), origin, flip);
		}
	}

	size_t SpriteSheet::getTileCount() const
	{
		return tileSheetDimension.w() * tileSheetDimension.h();
	}

	sdl::Point SpriteSheet::getTileSize() const
	{
		return tileSize;
	}
}