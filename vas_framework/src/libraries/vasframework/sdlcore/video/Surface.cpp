#include "Surface.hpp"

namespace sdl
{
	Surface::Surface()
	{
	}

	Surface::Surface(SDL_Surface * refInstance, SDLComponentBase::DeleterType deleter) :
		SDLComponentBase(refInstance, deleter)
	{
	}

	Surface::Surface(uint32_t flags, const Point & size, int depth, uint32_t rMask, uint32_t gMask, uint32_t bMask, uint32_t aMask) :
		SDLComponentBase(SDL_CreateRGBSurface(flags, size.x, size.y, depth, rMask, gMask, bMask, aMask), &defDeleter)
	{
	}

	/*Surface::Surface(uint32_t flags, const Point & size, int depth, uint32_t format) :
		SDLComponentBase(SDL_CreateRGBSurfaceWithFormat(flags, size.x, size.y, depth, format), &defDeleter)
	{
	}*/

	Surface::Surface(void * pixels, const Point & size, int depth, int pitch, uint32_t rMask, uint32_t gMask, uint32_t bMask, uint32_t aMask):
		SDLComponentBase(SDL_CreateRGBSurfaceFrom(pixels, size.x, size.y, depth, pitch, rMask, gMask, bMask, aMask), &defDeleter)
	{
	}

	/*Surface::Surface(void * pixels, const Point & size, int depth, int pitch, uint32_t format):
		SDLComponentBase(SDL_CreateRGBSurfaceWithFormatFrom(pixels, size.x, size.y, depth, pitch, format), &defDeleter)
	{
	}*/

	bool Surface::lock()
	{
		return SDL_LockSurface(&*this->componentInstance) == 0;
	}

	void Surface::loadBMP(std::string file)
	{
		loadBMPRw(SDL_RWFromFile(file.c_str(), "rb"));
	}

	void Surface::loadBMPRw(SDL_RWops * src, bool freeSrc)
	{
		SDL_Surface* temp = &*this->componentInstance;
		temp = SDL_LoadBMP_RW(src, freeSrc);
	}

	bool Surface::saveBMP(std::string file)
	{
		return saveBMPRw(SDL_RWFromFile(file.c_str(), "rb"));
	}

	bool Surface::saveBMPRw(SDL_RWops * dest, bool freeSrc)
	{
		return SDL_SaveBMP_RW(&*this->componentInstance, dest, freeSrc ? 1 : 0) == 0;
	}

	bool Surface::setPalette(SDL_Palette * palette)
	{
		return SDL_SetSurfacePalette(&*this->componentInstance, palette) == 0;
	}

	bool Surface::setRLE(int flags)
	{
		return SDL_SetSurfaceRLE(&*this->componentInstance, flags) == 0;
	}

	void Surface::unlock()
	{
		SDL_UnlockSurface(&*this->componentInstance);
	}

	Surface::Surface(const Surface & other):
		SDLComponentBase(other)
	{
	}

	Surface::Surface(Surface && other):
		SDLComponentBase(std::move(other.componentInstance))
	{
	}

	Surface::~Surface()
	{
	}

	Surface Surface::operator=(const Surface & rhs)
	{
		this->componentInstance = rhs.componentInstance;
		return *this;
	}

	Surface Surface::operator=(Surface && other)
	{
		this->componentInstance = std::move(other.componentInstance);
		return *this;
	}

	Surface & Surface::operator=(std::nullptr_t)
	{
		this->componentInstance = nullptr;
		return *this;
	}

	void Surface::defDeleter(SDL_Surface * instance)
	{
		SDL_FreeSurface(instance);
	}

	void Surface::notDeleteDeleter(SDL_Surface * instance)
	{
		return;
	}
}