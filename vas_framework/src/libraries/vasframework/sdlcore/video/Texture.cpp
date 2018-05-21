#include "Texture.hpp"

namespace sdl
{
	Texture::Texture()
	{
	}
	Texture::Texture(Renderer & renderer, uint32_t format, int access, const Point & size):
		SDLComponentBase(SDL_CreateTexture(static_cast<SDL_Renderer*>(renderer), format, access, size.x, size.y), &defDeleter)
	{
	}

	Texture::Texture(Renderer & renderer, Surface surface):
		SDLComponentBase(SDL_CreateTextureFromSurface(static_cast<SDL_Renderer*>(renderer), static_cast<SDL_Surface*>(surface)), &defDeleter)
	{
	}

	Texture::Texture(const Texture & other):
		SDLComponentBase(other)
	{
	}

	Texture::Texture(Texture && other):
		SDLComponentBase(std::move(other))
	{
	}

	Texture::Texture(SDL_Texture * other, SDLComponentBase::DeleterType deleter):
		SDLComponentBase(other, deleter)
	{
	}

	Texture::~Texture()
	{
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
		this->componentInstance = createRawComponent<SDL_Texture>(IMG_LoadTexture(static_cast<SDL_Renderer*>(renderer), file.c_str()), &defDeleter);
	}

	void Texture::loadImageRaw(Renderer & renderer, rwops::RWops * src, bool freeSrc)
	{
		this->componentInstance = createRawComponent<SDL_Texture>(IMG_LoadTexture_RW(static_cast<SDL_Renderer*>(renderer), src, freeSrc ? 1 : 0), &defDeleter);
	}

	void Texture::loadImageTypedRaw(Renderer & renderer, rwops::RWops * src, const std::string & type, bool freeSrc)
	{
		this->componentInstance = createRawComponent<SDL_Texture>(IMG_LoadTextureTyped_RW(static_cast<SDL_Renderer*>(renderer), src, freeSrc ? 1 : 0, type.c_str()), &defDeleter);
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

	Texture & Texture::operator=(const Texture & other)
	{
		this->componentInstance = other.componentInstance;
		return *this;
	}

	Texture& Texture::operator=(Texture && other)
	{
		this->componentInstance = std::move(other.componentInstance);
		return *this;
	}

	Texture & Texture::operator=(std::nullptr_t)
	{
		this->componentInstance = nullptr;
		return *this;
	}

	void Texture::VAS_PROTOTYPE_DEFINE_DEF_DELETER(SDL_Texture)
	{
		SDL_DestroyTexture(instance);
	}
}