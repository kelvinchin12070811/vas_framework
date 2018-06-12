#pragma once
#include <string>
#include "../../graphics/IRenderAble.hpp"
#include "../GraphicsFlags.hpp"
#include "../../sdlcore/video/Texture.hpp"
#include "../../sdlcore/math/Colour.hpp"
#include "../../sdlcore/math/Point.hpp"
#include "../../sdlcore/math/Rect.hpp"
#include "../../math/Vector2.hpp"
#include "../../math/Angle.hpp"
#include "../../manager/TextureManager.hpp"

namespace vas
{
	class Sprite : public IRenderAble
	{
	public:
		Sprite();
		Sprite(const std::string& file, const Vector2& position, const sdl::Point& origin = sdl::Point(), BufferMode bfMode = BufferMode::buffered);
		Sprite(const Sprite&) = delete;
		Sprite(Sprite&&) = delete;
		virtual ~Sprite();

		void move(const Vector2& movement);

		void setPosition(const Vector2& value);
		void setAngle(const Angle& value);
		void setOrigin(const sdl::Point& value);
		void setRendererFlip(sdl::Renderer::Flip flip);
		void setOverlay(const sdl::Colour& value);
		void setStaticOnCamera(bool value);

		Vector2 getPosition() const;
		Angle getAngle() const;
		sdl::Point getOrigin() const;
		sdl::Renderer::Flip getRendererFlip() const;
		sdl::Colour getOverlay() const;
		sdl::Rect getSourceRect() const;
		sdl::Rect getDestRect() const;
		bool isStaticOnCamera() const;

		int getWidth() const;
		int getHeight() const;

		void tick();
		void draw(sdl::Renderer* renderer = nullptr, Camera* camera = nullptr);

		Sprite& operator=(const Sprite&) = delete;
		Sprite& operator=(Sprite&&) = delete;
	protected:
		std::string filePath;
		Vector2 position;
		Angle angle;
		sdl::Point origin;
		sdl::Colour overlay;
		sdl::Rect source;
		sdl::Rect destination;
		sdl::Renderer::Flip rendererFlip{ sdl::Renderer::Flip::none };
		sdl::Texture texture;

		bool staticOnCamera = false;
	};
}