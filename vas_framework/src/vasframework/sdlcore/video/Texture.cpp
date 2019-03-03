//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "Texture.hpp"

namespace vas::sdl
{
	Texture::Texture()
	{
	}
	Texture::Texture(Renderer & renderer, uint32_t format, int access, const Point & size):
		componentInstance(std::shared_ptr<SDL_Texture>{ SDL_CreateTexture(static_cast<SDL_Renderer*>(renderer), format, access, size.x, size.y), &SDL_DestroyTexture })
	{
	}

	Texture::Texture(Renderer & renderer, Surface surface):
		componentInstance(std::shared_ptr<SDL_Texture>{ SDL_CreateTextureFromSurface(static_cast<SDL_Renderer*>(renderer), static_cast<SDL_Surface*>(surface)), &SDL_DestroyTexture })
	{
	}

	Texture::Texture(SDL_Texture * other, bool owner)
	{
		if (owner) componentInstance = std::shared_ptr<SDL_Texture>{ other, &SDL_DestroyTexture };
		else componentInstance = std::shared_ptr<SDL_Texture>{ other, [](SDL_Texture* i) { return; } };
	}

	bool Texture::getAlphaMod(uint8_t * alpha)
	{
		return SDL_GetTextureAlphaMod(&*this->componentInstance, alpha) == 0 ? true : false;
	}

	bool Texture::getBlendMod(BlendMode * mode)
	{
		return SDL_GetTextureBlendMode(&*this->componentInstance, reinterpret_cast<SDL_BlendMode*>(mode)) == 0 ? true : false;
	}

	bool Texture::getColorMod(uint8_t * red, uint8_t * green, uint8_t * bule)
	{
		return SDL_GetTextureColorMod(&*this->componentInstance, red, green, bule) == 0 ? true : false;
	}

	void Texture::loadImage(Renderer & renderer, const std::string & file)
	{
		this->componentInstance = std::shared_ptr<SDL_Texture>{ IMG_LoadTexture(static_cast<SDL_Renderer*>(renderer), file.c_str()), &SDL_DestroyTexture };
	}

	void Texture::loadImageRaw(Renderer & renderer, rwops::RWops * src, bool freeSrc)
	{
		this->componentInstance = std::shared_ptr<SDL_Texture>{ IMG_LoadTexture_RW(static_cast<SDL_Renderer*>(renderer), src, freeSrc ? 1 : 0), &SDL_DestroyTexture };
	}

	void Texture::loadImageTypedRaw(Renderer & renderer, rwops::RWops * src, const std::string & type, bool freeSrc)
	{
		this->componentInstance = std::shared_ptr<SDL_Texture>{ IMG_LoadTextureTyped_RW(static_cast<SDL_Renderer*>(renderer), src, freeSrc ? 1 : 0, type.c_str()), &SDL_DestroyTexture };
	}

	bool Texture::lockTexture(const Rect & rect, void ** pixels, int * pitch)
	{
		SDL_Rect temp = static_cast<SDL_Rect>(rect);
		return SDL_LockTexture(&*this->componentInstance, &temp, pixels, pitch) == 0 ? true : false;
	}

	bool Texture::setAlphaMod(uint8_t alpha)
	{
		return SDL_SetTextureAlphaMod(&*this->componentInstance, alpha) == 0 ? true : false;
	}

	bool Texture::setBlendMod(BlendMode mode)
	{
		return SDL_SetTextureBlendMode(&*this->componentInstance, static_cast<SDL_BlendMode>(mode)) == 0 ? true : false;
	}

	bool Texture::setColorMod(uint8_t red, uint8_t green, uint8_t bule)
	{
		return SDL_SetTextureColorMod(&*this->componentInstance, red, green, bule) == 0 ? true : false;
	}

	void Texture::unlockTexture()
	{
		SDL_UnlockTexture(&*this->componentInstance);
	}

	bool Texture::updateTexture(const Rect & rect, const void * pixels, int pitch)
	{
		SDL_Rect temp = static_cast<SDL_Rect>(rect);
		return SDL_UpdateTexture(&*this->componentInstance, &temp, pixels, pitch) == 0 ? true : false;
	}

	bool Texture::updateYUVTexture(const Rect & rect, const Uint8 * Yplane, int Ypitch, const Uint8 * Uplane, int Upitch, const Uint8 * Vplane, int Vpitch)
	{
		SDL_Rect temp = static_cast<SDL_Rect>(rect);
		return SDL_UpdateYUVTexture(&*this->componentInstance, &temp, Yplane, Ypitch, Uplane, Upitch, Vplane, Vpitch) == 0 ? true : false;
	}

	bool Texture::queryTexture(int * w, int * h)
	{
		return queryTexture(nullptr, nullptr, w, h);
	}

	bool Texture::queryTexture(uint32_t * format, int * access, int * w, int * h)
	{
		return SDL_QueryTexture(&*this->componentInstance, format, access, w, h) == 0 ? true : false;
	}
	
	void Texture::destroy()
	{
		componentInstance = nullptr;
	}

	bool Texture::isNull()
	{
		return componentInstance == nullptr;
	}

	Texture::operator SDL_Texture*()
	{
		return componentInstance.get();
	}
	
	bool Texture::operator==(const Texture & rhs)
	{
		return componentInstance == rhs.componentInstance;
	}
	
	bool Texture::operator!=(const Texture & rhs)
	{
		return !operator==(rhs);
	}
	
	bool Texture::operator==(NullComponent_t)
	{
		return isNull();
	}
	
	bool Texture::operator!=(NullComponent_t)
	{
		return !operator==(nullcomponent);
	}
	
	Texture & Texture::operator=(NullComponent_t)
	{
		destroy();
		return *this;
	}
}