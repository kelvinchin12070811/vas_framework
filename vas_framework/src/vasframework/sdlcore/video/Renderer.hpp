//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <SDL.h>
#include "../../VASConfig.hpp"
#include "../SDLComponentBase.hpp"
#include "Window.hpp"
#include "Surface.hpp"
#include "../Math.hpp"
#include "BlendMode.hpp"

namespace vas::sdl
{
	/**
	 * @ingroup sdl_basic
	 * @{
	 */
	using RendererInfo = SDL_RendererInfo; /**< Renderer Info struct. */
	/** @} */
	class Texture;
	/**
	 * @ingroup sdl_basic
	 * @{
	 */
	/** @brief The brush that draw every things to the Window. */
	class VAS_DECLSPEC Renderer
	{ /** @} */
	public:
		static const int defIndex; /**<default index of renderer driver. */
		/** Flipping effect of texture on renderer. */
		enum class Flip
		{
			/** Do not flip */
			none = 0x00000000,
			/** flip horizontally */
			horizontal = 0x00000001,
			/** flip vertically */
			vertical = 0x00000002
		};

		/** @brief renderer initialization flags. */
		struct RendererFlags
		{
			static const uint32_t software;         /**< The renderer is a software fallback */
			static const uint32_t accelerated;      /**< The renderer uses hardware
															* acceleration */
			static const uint32_t presentvsync;     /**< Present is synchronized
															* with the refresh rate */
			static const uint32_t targettexture;     /**< The renderer supports
															* rendering to texture */
		};

		Renderer(); /**< Create empty renderer instance. */
		/**
		 * Create new renderer instance.
		 * @param[in] window Window to render.
		 * @param[in] index driver to use, -1 to use default driver.
		 * @param[in] flags initialization flags of renderer, vas::sdl::Renderer::RendererFlags.
		 */
		Renderer(Window& window, int index, uint32_t flags);
		/** Create software renderer with raw component. */
		Renderer(SDL_Surface* surface);
		/** Create software renderer. */
		Renderer(Surface& surface);

		/**
		 * Reference constructor of Renderer.
		 * @param[in] renderer Raw component of renderer.
		 * @param[in] owner Determine if instance has ownership of @p renderer.
		 */
		explicit Renderer(SDL_Renderer* renderer, bool owner = false);

		/**
		 * Clear the renderer.
		 * @return true if success.
		 */
		bool clear();
		/**
		 * Draw texture to the renderer.
		 * @param[in] texture texture to render.
		 * @param[in] srcRect Source rect. nullptr for the entire texture.
		 * @param[in] destRect Destidation and size to render. nullptr to draw the entire screen.
		 * @return true if success.
		 */
		bool copy(Texture& texture, const Rect* srcRect, const Rect* destRect);
		/**
		 * Draw texture to the renderer.
		 * @param[in] texture texture to render.
		 * @param[in] srcRect Source rect. nullptr for the entire texture.
		 * @param[in] destRect Destidation and size to render. nullptr to draw the entire screen.
		 * @param[in] angle angle of the texture in degree.
		 * @param[in] center center point of the texture, or origin.
		 * @param[in] flip flip effect of the texture.
		 * @return true if success.
		 */
		bool copyEx(Texture& texture, const Rect* srcRect, const Rect* destRect, const double angle, const Point& center, Renderer::Flip flip = Renderer::Flip::none);
		
		/**
		 * Draw line on screen.
		 * @param[in] beginPos starting point.
		 * @param[in] endPos ending point.
		 * @return true if success.
		 */
		bool drawLine(const Point& beginPos, const Point& endPos);
		/**
		 * Draw multiple line.
		 * @param[in] points an array of points in pair for each line.
		 * @return true if success.
		 */
		bool drawLines(std::vector<Point>& points);
		/**
		 * Draw dot on screen.
		 * @param[in] position position of the dot.
		 * @return true if success.
		 */
		bool drawPoint(const Point& position);
		/**
		 * Draw multiple points.
		 * @param[in] points an array of points' position.
		 * @return true if success.
		 */
		bool drawPoints(std::vector<Point>& points);
		/**
		 * Draw rect on screen.
		 * @param[in] rect rect to draw, draw the entire render target if nullptr.
		 * @return true if success.
		 */
		bool drawRect(const Rect* rect);
		/**
		 * Draw multiple rects.
		 * @param[in] rects array of rects to draw.
		 * @return true if success.
		 */
		bool drawRects(std::vector<Rect>& rects);

		/**
		 * Fill rect on screen.
		 * @param[in] rect rect to fill, fill the entire render target if nullptr.
		 * @return true if success.
		 */
		bool fillRect(const Rect* rect);
		/**
		 * Fill multiple rects.
		 * @param[in] rects array of rects to fil.
		 * @return true if success.
		 */
		bool fillRects(std::vector<Rect>& rects);

		Rect getClipRect(); /**< Get clip rect for the current target. */
		bool getIntegerScale(); /**< Get whether integer scales are forced for resolution-independent rendering. */
		Point getLogicalSize(); /**< Get logical drawable size of the renderer. Letter box effect created if it does not matched up with target aspect ratio. */
		bool getRendererInfo(SDL_RendererInfo* rendererInfo); /**< Get renderer info for this renderer. */
		Point getOutputSize(); /**< Get output size of the renderer. */
		bool getRenderDrawBlendMode(BlendMode& blendMode); /**< Get the renderer global draw blend mode. */
		bool getRenderDrawColor(uint8_t* red, uint8_t* green, uint8_t* bule, uint8_t* alpha); /**< Get the colour use to draw. */
		Texture getRenderTarget(); /**< Get current render target. */
		void getScale(float* scaleX, float* scaleY); /**< Get drawing scale of current target. */
		Rect getViewPort(); /**< Get the current drawing area of current target. */

		bool isClipEnabled(); /**< Get whether clipping is enable on this this renderer. */

		/** Update the screen */
		void present();

		//Read the entire renderTarget if rect is nullptr
		bool readPixels(const Rect* rect, uint32_t format, void* pixels, int pitch); /**< Read pixels form the current rendering target. */
		bool renderTargetSupported(); /**< Determines whether a window support the rendering target. */

		bool setClipRect(const Rect& rect); /**< Set clip rect for current target. */
		bool setIntegerScale(bool visible); /**< Set whether to force integer scales for resolution-independent rendering */
		bool setLogicalSize(const Point& size); /**< Set device independent resolution for rendering */
		bool setRenderDrawBlendMode(BlendMode mode); /**< Set the blend mode used for drawing operations (Fill and Line). */
		bool setRenderDrawColor(uint8_t red, uint8_t green, uint8_t bule, uint8_t alpha); /**< Set the color used for drawing operations (Rect, Line and Clear). */
		bool setRenderTarget(Texture& texture); /**< Set a texture as the current rendering target. */
		bool setScale(float scaleX, float scaleY); /**< Set the drawing scale for rendering on the current target. */
		bool setViewPort(Rect& viewPortRect); /**< Set the drawing area for rendering on the current target. */

		RendererInfo getRendererInfo(); /**< Get the renderer info by returning a RendererInfo. */

		void destroy(); /**< Destroy instance. */
		bool isNull(); /**< Determine is this instance is nullcomponent. */

		/**
		 * @name Overloaded operators
		 * @{
		 */
		explicit operator SDL_Renderer*(); /**< Cast to raw component. */
		Renderer& operator=(NullComponent_t); /**< Destroy instance by assigning it to nullcomponent. */

		bool operator==(const Renderer& rhs); /**< Compare two instance if them equal. */
		bool operator==(NullComponent_t); /**< Determine if this instance is nullcomponent. */
		bool operator!=(const Renderer& rhs); /**< Compare two instance if them not equal. */
		bool operator!=(NullComponent_t); /**< Determine if this instance is not nullcomponent. */
		/** @} */

		static SDL_Renderer* getRendererFromWindow(SDL_Window* window); /**< Get the renderer associated with a SDL_Window. */
		static SDL_Renderer* getRendererFromWindow(Window& window); /**< Get the renderer associated with a sdl::Window. */
	private:
		std::shared_ptr<SDL_Renderer> componentInstance;
	};
}