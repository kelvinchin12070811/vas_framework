#pragma once
#include <string>
#include "../../graphics/DrawAble.hpp"
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
	/** @addtogroup graphics
		  @{
	*/
	/** @brief The spirit of the image and texture.

		  A sprite is a non-copyable object(possible with dynamic resource allocation) which represent an image buile from
		  texture that will be drawn on the renderer.

		  Sprite are able to move, rotate and other as it was the basic 2d elements.
	*/
	class VAS_DECLSPEC Sprite : public DrawAble
	{ /** @} */
	public:
		Sprite() = default;
		/** Create new sprite.
			  @param file Unique id or file name of the texture.
			  @param position Position of the sprite on renderer.
			  @param origin The center point or origin of the sprite, defalut is located at the top-left corner.
			  @param bfMode BufferMode of the texture.
		*/
		Sprite(const std::string& file, const Vector2& position, const sdl::Point& origin = sdl::Point(), BufferMode bfMode = BufferMode::buffered);
		Sprite(const Sprite&) = delete;
		Sprite(Sprite&&) = delete;
		virtual ~Sprite() = default;

		/** Move the sprite.
			  @param movement Steps (in pixel) which the sprite will move.
		*/
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

		/** Get the width of the sprite. */
		int getWidth() const;
		/** Get the height of the sprite. */
		int getHeight() const;

		void tick() override;
		void draw(sdl::Renderer* renderer = nullptr, Camera* camera = nullptr) override;

		Sprite& operator=(const Sprite&) = delete;
		Sprite& operator=(Sprite&&) = delete;
	protected:
		std::string filePath;
		/** [Read & Write] The position of the sprite.\n
				- __mutators__
					-# void setPosition(const Vector2& value)
				- __accessors__
					-# Vector2 getPosition() const
		*/
		Vector2 position;
		/** [Read & Write] The rotation angle of the sprite.\n
				- __mutators__
					-# void setAngle(const Angle& value)
				- __accessors__
					-# Angle getAngle() const
		*/
		Angle angle;
		/** [Read & Write] The origin (center point of rotation) of the sprite.\n
				- __mutators__
					-# void setOrigin(const sdl::Point& value)
				- __accessors__
					-# sdl::Point getOrigin() const
		*/
		sdl::Point origin;
		/** [Read & Write] The overlay colour of the sprite.\n
				- __mutators__
					-# void setOverlay(const sdl::Colour& value)
				- __accessors__
					-# sdl::Colour getOverlay() const
		*/
		sdl::Colour overlay{ sdl::ColourPresets::white };
		/** [Read Only] The source rect of the sprite.\n
				- __accessors__
					-# sdl::Rect getSourceRect() const
		*/
		sdl::Rect source;
		/** [Read Only] The destination rect of the sprite.\n
				- __accessors__
					-# sdl::Rect getDestRect() const
		*/
		sdl::Rect destination;
		/** [Read & Write] The flip of the sprite.\n
				- __mutators__
					-# void setRendererFlip(sdl::Renderer::Flip flip)
				- __accessors__
					-# sdl::Renderer::Flip getRendererFlip() const
		*/
		sdl::Renderer::Flip rendererFlip{ sdl::Renderer::Flip::none };
		sdl::Texture texture;

		/** [Read & Write] Determin if the object's movement affected by camera or not.\n
				- __mutators__
					-# void setStaticOnCamera(bool value)
				- __accessors__
					-# bool isStaticOnCamera() const
		*/
		bool staticOnCamera{ false };
	};
}