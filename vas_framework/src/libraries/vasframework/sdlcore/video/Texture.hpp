#pragma once
#include <SDL.h>
#include "../../VASConfig.hpp"
#include "Renderer.hpp"
#include "Surface.hpp"
#include "BlendMode.hpp"
#include "../Math.hpp"

namespace sdl
{
	class VAS_DECLSPEC Texture : public SDLComponentBase<SDL_Texture>
	{
	public:
		Texture(Renderer& renderer, uint32_t format, int access, const Point& size);
		Texture(Renderer& renderer, Surface& surface);
		Texture(const Texture& other);
		Texture(Texture&& other);
		explicit Texture(SDL_Texture* other, SDLComponentBase::DeleterType deleter = &Texture::defDeleter);
		~Texture();

		bool getAlphaMod(uint8_t* alpha);
		bool getBlendMod(BlendMode* mode);
		bool getColorMod(uint8_t* red, uint8_t* green, uint8_t* bule);

		bool lockTexture(const Rect& rect, void** pixels, int* pitch);

		bool setAlphaMod(uint8_t alpha);
		bool setBlendMod(BlendMode mode);
		bool setColorMod(uint8_t red, uint8_t green, uint8_t bule);

		void unlockTexture();
		//Note: This is a fairly slow function
		bool updateTexture(const Rect& rect, const void* pixels, int pitch);
		bool updateYUVTexture(const Rect& rect, const Uint8* Yplane, int Ypitch, const Uint8* Uplane, int Upitch, const Uint8* Vplane, int Vpitch);

		bool queryTexture(uint32_t* format, int* access, int* w, int* h);

		Texture& operator=(const Texture& other);
		Texture& operator=(Texture&& other);
		Texture& operator=(std::nullptr_t);
	private:
		static void defDeleter(SDL_Texture* instance);
		static void notDeleteDeleter(SDL_Texture* instance);
	};
}