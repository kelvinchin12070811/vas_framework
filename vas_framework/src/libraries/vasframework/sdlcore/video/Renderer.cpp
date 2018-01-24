#include "Renderer.hpp"
#include "../boolean_cast.hpp"
#include "Texture.hpp"

namespace sdl
{
	const int Renderer::defIndex = -1;

	const uint32_t Renderer::RendererFlags::software = 0x00000001;
	const uint32_t Renderer::RendererFlags::accelerated = 0x00000002;
	const uint32_t Renderer::RendererFlags::presentvsync = 0x00000004;
	const uint32_t Renderer::RendererFlags::targettexture = 0x00000008;

	Renderer::Renderer(Window & window, int index, uint32_t flags):
		SDLComponentBase(SDL_CreateRenderer(static_cast<SDL_Window*>(window), index, flags), &defDeleter)
	{
	}

	Renderer::Renderer(SDL_Surface * surface , SDLComponentBase::DeleterType deleter):
		SDLComponentBase(SDL_CreateSoftwareRenderer(surface), deleter)
	{
	}

	Renderer::Renderer(Surface & surface) :
		Renderer(static_cast<SDL_Surface*>(surface))
	{
	}

	Renderer::Renderer(SDL_Renderer * renderer):
		SDLComponentBase(renderer, &notDeleteDeleter)
	{
	}

	Renderer::Renderer(const Renderer & other):
		SDLComponentBase(other)
	{
	}

	Renderer::Renderer(Renderer && other):
		SDLComponentBase(std::move(other))
	{
	}

	Renderer::~Renderer()
	{
	}

	bool Renderer::clear()
	{
		return SDL_RenderClear(&*this->componentInstance) == 0 ? true : false;
	}

	bool Renderer::copy(Texture & texture, const Rect * srcRect, const Rect * destRect)
	{
		SDL_Rect first = srcRect == nullptr ? SDL_Rect{ 0 } : static_cast<SDL_Rect>(*srcRect);
		SDL_Rect second = destRect == nullptr ? SDL_Rect{ 0 } : static_cast<SDL_Rect>(*destRect);
		return SDL_RenderCopy(&*this->componentInstance, static_cast<SDL_Texture*>(texture),
			srcRect == nullptr ? nullptr : &first,
			destRect == nullptr ? nullptr: &second
		) == 0 ? true : false;
	}

	bool Renderer::copyEx(Texture & texture, const Rect * srcRect, const Rect * destRect, const double angle, const Point & center, Renderer::Flip flip)
	{
		auto desCenter = static_cast<SDL_Point>(center);
		auto desFlip = static_cast<SDL_RendererFlip>(flip);

		auto first = srcRect == nullptr ? SDL_Rect{ 0 } : static_cast<SDL_Rect>(*srcRect);
		auto second = destRect == nullptr ? SDL_Rect{ 0 } : static_cast<SDL_Rect>(*destRect);
		return SDL_RenderCopyEx(&*this->componentInstance, static_cast<SDL_Texture*>(texture),
			srcRect == nullptr ? nullptr : &first,
			destRect == nullptr ? nullptr : &second,
			angle, &desCenter, desFlip) == 0 ? true : false;
	}

	bool Renderer::drawLine(const Point & beginPos, const Point & endPos)
	{
		return SDL_RenderDrawLine(&*this->componentInstance, beginPos.x, beginPos.y, endPos.x, endPos.y) == 0 ? true : false;
	}

	bool Renderer::drawLines(std::vector<Point>& points)
	{
		std::vector<SDL_Point> desPoints;
		desPoints.reserve(points.size());
		for (auto itr = points.begin(); itr != points.end(); itr++)
			desPoints.push_back(static_cast<SDL_Point>(*itr));

		return SDL_RenderDrawLines(&*this->componentInstance, desPoints.data(), static_cast<int>(desPoints.size())) == 0 ? true : false;
	}

	bool Renderer::drawPoint(const Point & position)
	{
		return SDL_RenderDrawPoint(&*this->componentInstance, position.x, position.y) == 0 ? true : false;
	}

	bool Renderer::drawPoints(std::vector<Point>& points)
	{
		std::vector<SDL_Point> desPoints;
		desPoints.reserve(points.size());
		for (auto itr = points.begin(); itr != points.end(); itr++)
			desPoints.push_back(static_cast<SDL_Point>(*itr));

		return SDL_RenderDrawPoints(&*this->componentInstance, desPoints.data(), static_cast<int>(desPoints.size())) == 0 ? true : false;
	}

	bool Renderer::drawRect(const Rect * rect)
	{
		if (rect == nullptr)
			return SDL_RenderDrawRect(&*this->componentInstance, nullptr) == 0 ? true: false;
		
		auto desRect = static_cast<SDL_Rect>(*rect);
		return SDL_RenderDrawRect(&*this->componentInstance, &desRect) == 0 ? true : false;
	}

	bool Renderer::drawRects(std::vector<Rect>& rects)
	{
		std::vector<SDL_Rect> desRects;
		desRects.reserve(rects.size());
		for (auto itr = rects.begin(); itr != rects.end(); itr++)
			desRects.push_back(static_cast<SDL_Rect>(*itr));

		return SDL_RenderDrawRects(&*this->componentInstance, desRects.data(), static_cast<int>(desRects.size())) == 0 ? true : false;
	}

	bool Renderer::fillRect(const Rect * rect)
	{
		if (rect == nullptr)
			return SDL_RenderFillRect(&*this->componentInstance, nullptr) == 0 ? true : false;

		SDL_Rect tempRect = static_cast<SDL_Rect>(*rect);
		return SDL_RenderFillRect(&*this->componentInstance, &tempRect) == 0 ? true : false;
	}

	bool Renderer::fillRects(std::vector<Rect>& rects)
	{
		std::vector<SDL_Rect> desRects;
		desRects.reserve(rects.size());
		for (auto itr = rects.begin(); itr != rects.end(); itr++)
			desRects.push_back(static_cast<SDL_Rect>(*itr));

		return SDL_RenderFillRects(&*this->componentInstance, desRects.data(), desRects.size()) == 0 ? true : false;
	}

	Rect Renderer::getClipRect()
	{
		SDL_Rect temp;
		SDL_RenderGetClipRect(&*this->componentInstance, &temp);
		return static_cast<Rect>(temp);
	}

	bool Renderer::getIntegerScale()
	{
		return boolean_cast(SDL_RenderGetIntegerScale(&*this->componentInstance));
	}

	Point Renderer::getLogicalSize()
	{
		Point logicalSize;
		SDL_RenderGetLogicalSize(&*this->componentInstance, &logicalSize.x, &logicalSize.y);
		return logicalSize;
	}

	bool Renderer::getRendererInfo(SDL_RendererInfo * rendererInfo)
	{
		return SDL_GetRendererInfo(&*this->componentInstance, rendererInfo) == 0 ? true : false;
	}

	Point Renderer::getOutputSize()
	{
		Point outputSize;
		SDL_GetRendererOutputSize(&*this->componentInstance, &outputSize.x, &outputSize.y);
		return outputSize;
	}

	bool Renderer::getRenderDrawBlendMode(BlendMode & blendMode)
	{
		SDL_BlendMode temp;
		auto result = SDL_GetRenderDrawBlendMode(&*this->componentInstance, &temp);
		blendMode = static_cast<BlendMode>(temp);
		return result == 0 ? true : false;
	}

	bool Renderer::getRenderDrawColor(uint8_t * red, uint8_t * green, uint8_t * bule, uint8_t * alpha)
	{
		return SDL_GetRenderDrawColor(&*this->componentInstance, red, green, bule, alpha) == 0 ? true : false;
	}

	Texture Renderer::getRenderTarget()
	{
		return static_cast<Texture>(SDL_GetRenderTarget(&*this->componentInstance));
	}

	void Renderer::getScale(float * scaleX, float * scaleY)
	{
		SDL_RenderGetScale(&*this->componentInstance, scaleX, scaleY);
	}

	Rect Renderer::getViewPort()
	{
		SDL_Rect temp;
		SDL_RenderGetViewport(&*this->componentInstance, &temp);
		return static_cast<Rect>(temp);
	}

	bool Renderer::isClipEnabled()
	{
		return boolean_cast(SDL_RenderIsClipEnabled(&*this->componentInstance));
	}

	void Renderer::present()
	{
		SDL_RenderPresent(&*this->componentInstance);
	}

	bool Renderer::readPixels(const Rect * rect, uint32_t format, void * pixels, int pitch)
	{
		if (rect == nullptr)
			return SDL_RenderReadPixels(&*this->componentInstance, nullptr, format, pixels, pitch) == 0 ? true : false;

		SDL_Rect desRect = static_cast<SDL_Rect>(*rect);
		return SDL_RenderReadPixels(&*this->componentInstance, &desRect, format, pixels, pitch) == 0 ? true : false;
	}

	bool Renderer::renderTargetSupported()
	{
		return boolean_cast(SDL_RenderTargetSupported(&*this->componentInstance));
	}

	bool Renderer::setClipRect(const Rect & rect)
	{
		auto temp = static_cast<SDL_Rect>(rect);
		return SDL_RenderSetClipRect(&*this->componentInstance, &temp) == 0 ? true : false;
	}

	bool Renderer::setIntegerScale(bool enable)
	{
		return SDL_RenderSetIntegerScale(&*this->componentInstance, boolean_cast(enable)) == 0 ? true : false;
	}

	bool Renderer::setLogicalSize(const Point & size)
	{
		return SDL_RenderSetLogicalSize(&*this->componentInstance, size.x, size.y) == 0 ? true : false;
	}

	bool Renderer::setRenderDrawBlendMode(BlendMode mode)
	{
		auto temp = static_cast<SDL_BlendMode>(mode);
		return SDL_SetRenderDrawBlendMode(&*this->componentInstance, temp) == 0 ? true : false;
	}

	bool Renderer::setRenderDrawColor(uint8_t red, uint8_t green, uint8_t bule, uint8_t alpha)
	{
		return SDL_SetRenderDrawColor(&*this->componentInstance, red, green, bule, alpha) == 0 ? true : false;
	}

	bool Renderer::setRenderTarget(Texture & texture)
	{
		return SDL_SetRenderTarget(&*this->componentInstance, static_cast<SDL_Texture*>(texture)) == 0 ? true : false;
	}

	bool Renderer::setScale(float scaleX, float scaleY)
	{
		return SDL_RenderSetScale(&*this->componentInstance, scaleX, scaleY) == 0 ? true : false;
	}

	bool Renderer::setViewPort(Rect & viewPortRect)
	{
		auto temp = static_cast<SDL_Rect>(viewPortRect);
		return SDL_RenderSetViewport(&*this->componentInstance, &temp) == 0 ? true : false;
	}

	/*Renderer::operator const SDL_Renderer*() const
	{
		return &*this->componentInstance;
	}

	Renderer::operator SDL_Renderer*()
	{
		return const_cast<SDL_Renderer*>(this->operator const SDL_Renderer *());
	}*/

	Renderer& Renderer::operator=(const Renderer & other)
	{
		this->componentInstance = other.componentInstance;
		return *this;
	}

	Renderer& Renderer::operator=(Renderer && other)
	{
		this->componentInstance = std::move(other.componentInstance);
		return *this;
	}

	Renderer & Renderer::operator=(std::nullptr_t)
	{
		this->componentInstance = nullptr;
		return *this;
	}

	SDL_Renderer * Renderer::getRendererFromWindow(SDL_Window * window)
	{
		return SDL_GetRenderer(window);
	}

	SDL_Renderer * Renderer::getRendererFromWindow(Window & window)
	{
		return getRendererFromWindow(static_cast<SDL_Window*>(window));
	}

	void Renderer::VAS_PROTOTYPE_DEFINE_DEF_DELETER(SDL_Renderer)
	{
		SDL_DestroyRenderer(instance);
	}
}