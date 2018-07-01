#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "../../VASConfig.hpp"
#include "../SDLComponentBase.hpp"
#include "../Math.hpp"
#include "../RWops.hpp"

namespace vas::sdl
{
	class VAS_DECLSPEC Surface : public SDLComponentBase<SDL_Surface, Surface>
	{
	public:
		Surface();
		explicit Surface(SDL_Surface* refInstance, SDLComponentBase::DeleterType deleter = &Surface::notDeleteDeleter);
		Surface(uint32_t flags, const Point& size, int depth, uint32_t rMask, uint32_t gMask, uint32_t bMask, uint32_t aMask);
		//Surface(uint32_t flags, const Point& size, int depth, uint32_t format);
		Surface(void* pixels, const Point& size, int depth, int pitch, uint32_t rMask, uint32_t gMask, uint32_t bMask, uint32_t aMask);
		//Surface(void* pixels, const Point& size, int depth, int pitch, uint32_t format);

		bool lock();
		void loadBMP(std::string file);
		void loadBMPRw(sdl::rwops::RWops* src, bool freeSrc = true);
		void loadImage(const std::string& file);
		void loadImageRaw(sdl::rwops::RWops* src, bool freeSrc = true);

		/* Load an image from an SDL data source.
		The 'type' may be one of: "BMP", "GIF", "PNG", etc.

		If the image format supports a transparent pixel, SDL will set the
		colorkey for the surface.  You can enable RLE acceleration on the
		surface afterwards by calling:
		SDL_SetColorKey(image, SDL_RLEACCEL, image->format->colorkey);
		*/
		void loadIMGTypedRW(sdl::rwops::RWops* src, const std::string& type, bool freeSrc = true);

		bool saveBMP(const std::string& file);
		bool saveBMPRw(sdl::rwops::RWops* dest, bool freeSrc = true);
		bool savePNG(const std::string& file);
		bool savePNGRaw(sdl::rwops::RWops* dest, bool freeDst = true);
		bool setPalette(SDL_Palette* palette);
		bool setRLE(int flags);

		void unlock();

		Surface(const Surface& other);
		Surface(Surface&& other);
		~Surface();

		Surface operator=(const Surface& rhs);
		Surface operator=(Surface&& other);
		Surface& operator=(std::nullptr_t);

		static void VAS_PROTOTYPE_DEFINE_DEF_DELETER(SDL_Surface);
	};
}