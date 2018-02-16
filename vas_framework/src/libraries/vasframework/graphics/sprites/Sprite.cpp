#include "Sprite.hpp"
#include "../../base/Base.hpp"

namespace vas
{
	Sprite::Sprite()
	{
	}

	Sprite::Sprite(const std::string & file, const Vector2D & position, const sdl::Point & origin, BufferMode bfMode):
		filePath(file), position(position), origin(origin)
	{
		if (bfMode == BufferMode::buffered)
		{
			if (TextureManager::getInstance().has(file))
			{
				texture = TextureManager::getInstance().get(file);
			}
			else
			{
				texture.loadImage(Base::getInstance().Renderer(), file);
				TextureManager::getInstance().insert(file, texture);
			}
		}
		else
		{
			texture.loadImage(Base::getInstance().Renderer(), file);
		}
		if (texture == sdl::emptycomponent)
			throw sdl::SDLCoreException();

		texture.queryTexture(&source.w, &source.h);
		destination = source;
	}

	Sprite::~Sprite()
	{
	}

	void Sprite::move(const Vector2D & movement)
	{
		this->position += movement;
	}

	void Sprite::setPosition(const Vector2D & value)
	{
		if (this->position != value)
			this->position = value;
	}

	void Sprite::setAngle(const Angle & value)
	{
		if (this->angle != value)
			this->angle = value;
	}

	void Sprite::setOrigin(const sdl::Point & value)
	{
		if (this->origin != value)
			this->origin = value;
	}

	void Sprite::setRendererFlip(sdl::Renderer::Flip flip)
	{
		if (this->rendererFlip != flip)
			this->rendererFlip = flip;
	}

	void Sprite::setOverlay(const sdl::Colour & value)
	{
		if (this->overlay != value)
		{
			this->overlay = value;
			texture.setColorMod(value.red, value.green, value.bule);
			texture.setAlphaMod(value.alpha);
		}
	}

	Vector2D Sprite::getPosition() const
	{
		return position;
	}

	Angle Sprite::getAngle() const
	{
		return angle;
	}

	sdl::Point Sprite::getOrigin() const
	{
		return origin;
	}

	sdl::Renderer::Flip Sprite::getRendererFlip() const
	{
		return rendererFlip;
	}

	sdl::Colour Sprite::getOverlay() const
	{
		return overlay;
	}

	void Sprite::tick()
	{
		if (static_cast<int>(position.x) != destination.x)
			destination.x = static_cast<int>(position.x);

		if (static_cast<int>(position.y) != destination.y)
			destination.y = static_cast<int>(destination.y);
	}

	void Sprite::draw()
	{
		if (texture == sdl::emptycomponent) return;

		auto renderer = Base::getInstance().Renderer();
		renderer.copyEx(texture, &source, &destination, static_cast<double>(angle), origin, rendererFlip);
	}
}