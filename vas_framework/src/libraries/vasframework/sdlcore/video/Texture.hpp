#pragma once
#include <SDL.h>
#include "../../VASConfig.hpp"
#include "Renderer.hpp"
#include "Surface.hpp"
#include "BlendMode.hpp"
#include "../Math.hpp"
#include "../RWops.hpp"

namespace sdl
{
	class VAS_DECLSPEC Texture : public SDLComponentBase<SDL_Texture, Texture>
	{
	public:
		Texture();
		Texture(Renderer& renderer, uint32_t format, int access, const Point& size);
		Texture(Renderer& renderer, Surface& surface);
		Texture(const Texture& other);
		Texture(Texture&& other);
		explicit Texture(SDL_Texture* other, SDLComponentBase::DeleterType deleter = &Texture::notDeleteDeleter);
		~Texture();

		bool getAlphaMod(uint8_t* alpha);
		bool getBlendMod(BlendMode* mode);
		bool getColorMod(uint8_t* red, uint8_t* green, uint8_t* bule);

		void loadImage(Renderer& renderer, const std::string& file);
		void loadImageRaw(Renderer& renderer, rwops::RWops* src, bool freeSrc = true);

		/* Load an image from an SDL data source.
		The 'type' may be one of: "BMP", "GIF", "PNG", etc.

		If the image format supports a transparent pixel, SDL will set the
		colorkey for the surface.  You can enable RLE acceleration on the
		surface afterwards by calling:
		SDL_SetColorKey(image, SDL_RLEACCEL, image->format->colorkey);
		*/
		void loadImageTypedRaw(Renderer& renderer, rwops::RWops* src, const std::string& type, bool freeSrc = true);
		bool lockTexture(const Rect& rect, void** pixels, int* pitch);

		bool setAlphaMod(uint8_t alpha);
		bool setBlendMod(BlendMode mode);
		bool setColorMod(uint8_t red, uint8_t green, uint8_t bule);

		void unlockTexture();
		//Note: This is a fairly slow function
		bool updateTexture(const Rect& rect, const void* pixels, int pitch);
		bool updateYUVTexture(const Rect& rect, const Uint8* Yplane, int Ypitch, const Uint8* Uplane, int Upitch, const Uint8* Vplane, int Vpitch);

		bool queryTexture(int* w, int* h);
		bool queryTexture(uint32_t* format, int* access, int* w, int* h);

		Texture& operator=(const Texture& other);
		Texture& operator=(Texture&& other);
		Texture& operator=(std::nullptr_t);

		static void VAS_PROTOTYPE_DEFINE_DEF_DELETER(SDL_Texture);
	};
}