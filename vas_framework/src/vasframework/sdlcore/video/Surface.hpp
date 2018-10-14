#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "../../VASConfig.hpp"
#include "../SDLComponentBase.hpp"
#include "../Math.hpp"
#include "../RWops.hpp"

namespace vas::sdl
{
	/** @addtogroup sdl_basic
		  @{
	*/
	/** @brief A collection of pixels used in software blitting. */
	class VAS_DECLSPEC Surface : public SDLComponentBase<SDL_Surface, Surface>
	{ /** @} */
	public:
		Surface(); /**< Create empty surface. */
		/** Refrence to a SDL_Surface. */
		explicit Surface(SDL_Surface* refInstance, SDLComponentBase::DeleterType deleter = &Surface::notDeleteDeleter);
		/** Create new surface with raw rgba mask. */
		Surface(uint32_t flags, const Point& size, int depth, uint32_t rMask, uint32_t gMask, uint32_t bMask, uint32_t aMask);
		//Surface(uint32_t flags, const Point& size, int depth, uint32_t format);
		/** Create RGB surface form @p pixels. */
		Surface(void* pixels, const Point& size, int depth, int pitch, uint32_t rMask, uint32_t gMask, uint32_t bMask, uint32_t aMask);
		//Surface(void* pixels, const Point& size, int depth, int pitch, uint32_t format);

		bool lock(); /**< lock the surface. */
		void loadBMP(std::string file); /**< load only BMP image from @p file. */
		void loadBMPRw(sdl::rwops::RWops* src, bool freeSrc = true); /**< load only BMP image from memory. */
		void loadImage(const std::string& file); /**< load any kind of supported image from @p file. */
		void loadImageRaw(sdl::rwops::RWops* src, bool freeSrc = true); /**< load and supported image from memory. */

		/** Load an image from an SDL data source.
		The 'type' may be one of: "BMP", "GIF", "PNG", etc.

		If the image format supports a transparent pixel, SDL will set the
		colorkey for the surface.  You can enable RLE acceleration on the
		surface afterwards by calling:
		SDL_SetColorKey(image, SDL_RLEACCEL, image->format->colorkey);
		*/
		void loadIMGTypedRW(sdl::rwops::RWops* src, const std::string& type, bool freeSrc = true);

		bool saveBMP(const std::string& file); /**< save current surface to bmp file at @p file. */
		bool saveBMPRw(sdl::rwops::RWops* dest, bool freeSrc = true); /**< Dump current surface to bmp in ram. */
		bool savePNG(const std::string& file); /**< Save current surface to png file. */
		bool savePNGRaw(sdl::rwops::RWops* dest, bool freeDst = true); /**< dump current surface in memory with png format. */
		bool setPalette(SDL_Palette* palette); /**< Set the palette use by the surface. */
		bool setRLE(int flags); /**< Set the RLE acceleration of the surface. */

		void unlock(); /**< unlock surface. */

		Surface(const Surface& other);
		Surface(Surface&& other);
		~Surface();

		Surface operator=(const Surface& rhs);
		Surface operator=(Surface&& other);
		Surface& operator=(std::nullptr_t);

		static void VAS_PROTOTYPE_DEFINE_DEF_DELETER(SDL_Surface);
	};
}