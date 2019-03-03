//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "Surface.hpp"

namespace vas::sdl
{
	Surface::Surface()
	{
	}

	Surface::Surface(SDL_Surface * refInstance, bool owner)
	{
		if (owner) componentInstance = std::shared_ptr<SDL_Surface>{ refInstance, &SDL_FreeSurface };
		else componentInstance = std::shared_ptr<SDL_Surface>{ refInstance, [](SDL_Surface* i) { return; } };
	}

	Surface::Surface(uint32_t flags, const Point & size, int depth, uint32_t rMask, uint32_t gMask, uint32_t bMask, uint32_t aMask) :
		componentInstance(std::shared_ptr<SDL_Surface>{ SDL_CreateRGBSurface(flags, size.x, size.y, depth, rMask, gMask, bMask, aMask), &SDL_FreeSurface })
	{
	}

	Surface::Surface(void * pixels, const Point & size, int depth, int pitch, uint32_t rMask, uint32_t gMask, uint32_t bMask, uint32_t aMask):
		componentInstance(std::shared_ptr<SDL_Surface>{ SDL_CreateRGBSurfaceFrom(pixels, size.x, size.y, depth, pitch, rMask, gMask, bMask, aMask), &SDL_FreeSurface })
	{
	}

	bool Surface::lock()
	{
		return SDL_LockSurface(&*this->componentInstance) == 0;
	}

	void Surface::loadBMP(std::string file)
	{
		loadBMPRw(SDL_RWFromFile(file.c_str(), "rb"));
	}

	void Surface::loadBMPRw(sdl::rwops::RWops * src, bool freeSrc)
	{
		this->componentInstance = std::shared_ptr<SDL_Surface>{ SDL_LoadBMP_RW(src, (freeSrc ? 1 : 0)), &SDL_FreeSurface };
	}

	void Surface::loadImage(const std::string & file)
	{
		this->componentInstance = std::shared_ptr<SDL_Surface>{ IMG_Load(file.c_str()), &SDL_FreeSurface };
	}

	void Surface::loadImageRaw(sdl::rwops::RWops * src, bool freeSrc)
	{
		this->componentInstance = std::shared_ptr<SDL_Surface>{ IMG_Load_RW(src, (freeSrc ? 1 : 0)), &SDL_FreeSurface };
	}

	void Surface::loadIMGTypedRW(sdl::rwops::RWops * src, const std::string & type, bool freeSrc)
	{
		this->componentInstance = std::shared_ptr<SDL_Surface>{ IMG_LoadTyped_RW(src, (freeSrc ? 1 : 0), type.c_str()), &SDL_FreeSurface };
	}

	bool Surface::saveBMP(const std::string& file)
	{
		return saveBMPRw(SDL_RWFromFile(file.c_str(), "wb"));
	}

	bool Surface::saveBMPRw(sdl::rwops::RWops * dest, bool freeSrc)
	{
		return SDL_SaveBMP_RW(&*this->componentInstance, dest, freeSrc ? 1 : 0) == 0;
	}

	bool Surface::savePNG(const std::string & file)
	{
		return IMG_SavePNG(&*this->componentInstance, file.c_str()) == 0;
	}

	bool Surface::savePNGRaw(sdl::rwops::RWops * dest, bool freeDst)
	{
		return IMG_SavePNG_RW(&*this->componentInstance, dest, (freeDst ? 1 : 0)) == 0;
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

	bool Surface::operator==(const Surface & rhs)
	{
		return componentInstance == rhs.componentInstance;
	}
	
	bool Surface::operator!=(const Surface & rhs)
	{
		return !operator==(rhs);
	}
	
	bool Surface::operator==(NullComponent_t)
	{
		return isNull();
	}
	
	bool Surface::operator!=(NullComponent_t)
	{
		return !operator==(nullcomponent);
	}

	Surface & Surface::operator=(NullComponent_t)
	{
		destroy();
		return *this;
	}

	Surface::operator SDL_Surface*()
	{
		return componentInstance.get();
	}

	void Surface::destroy()
	{
		componentInstance = nullptr;
	}

	bool Surface::isNull()
	{
		return componentInstance == nullptr;
	}
}