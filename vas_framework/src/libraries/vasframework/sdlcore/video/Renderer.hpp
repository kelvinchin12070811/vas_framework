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
	using RendererInfo = SDL_RendererInfo;
	class Texture;
	class VAS_DECLSPEC Renderer : public SDLComponentBase<SDL_Renderer, Renderer>
	{
	public:
		static const int defIndex;
		enum class Flip
		{
			/**< Do not flip */
			none = 0x00000000,
			/**< flip horizontally */
			horizontal = 0x00000001,
			/**< flip vertically */
			vertical = 0x00000002
		};

		struct RendererFlags
		{
			static const uint32_t software;         /**< The renderer is a software fallback */
			static const uint32_t accelerated;      /**< The renderer uses hardware
															acceleration */
			static const uint32_t presentvsync;     /**< Present is synchronized
															with the refresh rate */
			static const uint32_t targettexture;     /**< The renderer supports
															rendering to texture */
		};

		Renderer();
		Renderer(Window& window, int index, uint32_t flags);
		Renderer(SDL_Surface* surface, SDLComponentBase::DeleterType deleter = &Renderer::notDeleteDeleter);
		Renderer(Surface& surface);
		explicit Renderer(SDL_Renderer* renderer);

		Renderer(const Renderer& other);
		Renderer(Renderer&& other);
		~Renderer();

		bool clear();
		bool copy(Texture& texture, const Rect* srcRect, const Rect* destRect);
		bool copyEx(Texture& texture, const Rect* srcRect, const Rect* destRect, const double angle, const Point& center, Renderer::Flip flip = Renderer::Flip::none);

		bool drawLine(const Point& beginPos, const Point& endPos);
		bool drawLines(std::vector<Point>& points);
		bool drawPoint(const Point& position);
		bool drawPoints(std::vector<Point>& points);
		//Draw the entire render target if nullptr
		bool drawRect(const Rect* rect);
		bool drawRects(std::vector<Rect>& rects);

		//Fill the entire render target if nullptr
		bool fillRect(const Rect* rect);
		bool fillRects(std::vector<Rect>& rects);

		Rect getClipRect();
		bool getIntegerScale();
		Point getLogicalSize();
		bool getRendererInfo(SDL_RendererInfo* rendererInfo);
		Point getOutputSize();
		bool getRenderDrawBlendMode(BlendMode& blendMode);
		bool getRenderDrawColor(uint8_t* red, uint8_t* green, uint8_t* bule, uint8_t* alpha);
		Texture getRenderTarget();
		void getScale(float* scaleX, float* scaleY);
		Rect getViewPort();

		bool isClipEnabled();

		//Update the screen
		void present();

		//Read the entire renderTarget if rect is nullptr
		bool readPixels(const Rect* rect, uint32_t format, void* pixels, int pitch);
		bool renderTargetSupported();

		bool setClipRect(const Rect& rect);
		bool setIntegerScale(bool visible);
		bool setLogicalSize(const Point& size);
		bool setRenderDrawBlendMode(BlendMode mode);
		bool setRenderDrawColor(uint8_t red, uint8_t green, uint8_t bule, uint8_t alpha);
		bool setRenderTarget(Texture& texture);
		bool setScale(float scaleX, float scaleY);
		bool setViewPort(Rect& viewPortRect);

		RendererInfo getRendererInfo();

		/*explicit operator const SDL_Renderer*() const;
		explicit operator SDL_Renderer*();*/
		Renderer& operator=(const Renderer& other);
		Renderer& operator=(Renderer&& other);
		Renderer& operator=(std::nullptr_t);

		static SDL_Renderer* getRendererFromWindow(SDL_Window* window);
		static SDL_Renderer* getRendererFromWindow(Window& window);
		static void VAS_PROTOTYPE_DEFINE_DEF_DELETER(SDL_Renderer);
	};
}