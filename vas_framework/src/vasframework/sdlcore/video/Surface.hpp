//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../../VASConfig.hpp"
#include "../SDLComponentBase.hpp"
#include "../Math.hpp"
#include "../RWops.hpp"

namespace vas::sdl
{
	/**
	 * @ingroup sdl_basic
	 * @{
	 */
	/** @brief A collection of pixels used in software blitting. */
	class VAS_DECLSPEC Surface
	{ /** @} */
	public:
		Surface(); /**< Create empty surface. */
		/**
		 * Refrence to a SDL_Surface.
		 * @param[in] refInstance Instance to raw component.
		 * @param[in] owner Determine if object own the instance. Handle memory management if true.
		 */
		explicit Surface(SDL_Surface* refInstance, bool owner = false);
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

		/**
		 * Load an image from an SDL data source.
		 * The 'type' may be one of: "BMP", "GIF", "PNG", etc.
		 * 
		 * If the image format supports a transparent pixel, SDL will set the
		 * colorkey for the surface.  You can enable RLE acceleration on the
		 * surface afterwards by calling:
		 * SDL_SetColorKey(image, SDL_RLEACCEL, image->format->colorkey);
		 */
		void loadIMGTypedRW(sdl::rwops::RWops* src, const std::string& type, bool freeSrc = true);

		bool saveBMP(const std::string& file); /**< save current surface to bmp file at @p file. */
		bool saveBMPRw(sdl::rwops::RWops* dest, bool freeSrc = true); /**< Dump current surface to bmp in ram. */
		bool savePNG(const std::string& file); /**< Save current surface to png file. */
		bool savePNGRaw(sdl::rwops::RWops* dest, bool freeDst = true); /**< dump current surface in memory with png format. */
		bool setPalette(SDL_Palette* palette); /**< Set the palette use by the surface. */
		bool setRLE(int flags); /**< Set the RLE acceleration of the surface. */

		void unlock(); /**< unlock surface. */

		/**
		 * @name Overloaded operators
		 * @{
		 */
		bool operator==(const Surface& rhs); /**< Compare if two instances are equal. */
		bool operator!=(const Surface& rhs); /**< Compare if two instances are not equal. */
		bool operator==(NullComponent_t); /**< Compare if this instance is equal to nullcomponent. */
		bool operator!=(NullComponent_t); /**< Compare if this instance is not nullcomponent. */

		Surface& operator=(NullComponent_t); /**< Destroy this instance by assigning it to nullcomponent. */
		explicit operator SDL_Surface*(); /**< Cast instance back to SDL_Surface* */
		/** @} */
		void destroy(); /**< Destroy instance. */
		bool isNull(); /**< Check if null. */

		std::shared_ptr<SDL_Surface> componentInstance;
	};
}