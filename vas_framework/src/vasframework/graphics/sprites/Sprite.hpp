//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
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
	/**
	 * @ingroup graphics
	 * @{
	 */
	/**
	 * @brief The spirit of the image and texture.
	 * 
	 * A sprite is a non-copyable object(possible with dynamic resource allocation) which represent an image buile from
	 * texture that will be drawn on the renderer.
	 * 
	 * Sprite are able to move, rotate and other as it was the basic 2d elements.
	 */
	class VAS_DECLSPEC Sprite : public DrawAble
	{ /** @} */
	public:
		Sprite() = default;
		/**
		 * Create new sprite.
		 * @param[in] file Unique id or file name of the texture.
		 * @param[in] position Position of the sprite on renderer.
		 * @param[in] origin The center point or origin of the sprite, defalut is located at the top-left corner.
		 * @param[in] bfMode BufferMode of the texture.
		 * @throw vas::sdl::SDLCoreException if creation of texture failed.
		 */
		Sprite(const std::string& file, const Vector2& position, const sdl::Point& origin = sdl::Point(), BufferMode bfMode = BufferMode::buffered);
		Sprite(const Sprite&) = delete;
		Sprite(Sprite&&) = delete;
		virtual ~Sprite() = default;

		/**
		 * Move the sprite.
		 * @param[in] movement Steps (in pixel) which the sprite will move.
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
		/**
		 * The position of the sprite.
		 *
		 * ####Mutators
		 * -# void setPosition(const Vector2& value)
		 *
		 * ####Accessors
		 * -# Vector2 getPosition() const
		 */
		Vector2 position;
		/**
		 * The rotation angle of the sprite.
		 * - __mutators__
		 * -# void setAngle(const Angle& value)
		 * 
		 * - __accessors__
		 * -# Angle getAngle() const
		 */
		Angle angle;
		/**
		 * The origin (center point of rotation) of the sprite.
		 * - __mutators__
		 * -# void setOrigin(const sdl::Point& value)
		 * 
		 * ####Accessors
		 * -# sdl::Point getOrigin() const
		 */
		sdl::Point origin;
		/**
		 * The overlay colour of the sprite.
		 * ####Mutators
		 * -# void setOverlay(const sdl::Colour& value)
		 * 
		 * ####Accessors
		 * -# sdl::Colour getOverlay() const
		 */
		sdl::Colour overlay{ sdl::ColourPresets::white };
		/**
		 * The source rect of the sprite.
		 * ####Accessors
		 * -# sdl::Rect getSourceRect() const
		 */
		sdl::Rect source;
		/**
		 * The destination rect of the sprite.
		 * ####Accessors
		 * -# sdl::Rect getDestRect() const
		 */
		sdl::Rect destination;
		/**
		 * The flip of the sprite.
		 * ####Mutators
		 * -# void setRendererFlip(sdl::Renderer::Flip flip)
		 * 
		 * ####Accessors
		 * -# sdl::Renderer::Flip getRendererFlip() const
		 */
		sdl::Renderer::Flip rendererFlip{ sdl::Renderer::Flip::none };
		sdl::Texture texture;

		/**
		 * Determin if the object's movement affected by camera or not.
		 * ####Mutators
		 * -# void setStaticOnCamera(bool value)
		 * 
		 * ####Accessors
		 * -# bool isStaticOnCamera() const
		 */
		bool staticOnCamera{ false };
	};
}