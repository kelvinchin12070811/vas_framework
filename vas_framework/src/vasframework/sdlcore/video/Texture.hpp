//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <SDL.h>
#include "../../VASConfig.hpp"
#include "Renderer.hpp"
#include "Surface.hpp"
#include "BlendMode.hpp"
#include "../Math.hpp"
#include "../RWops.hpp"

namespace vas::sdl
{
	/**
	 * @ingroup sdl_basic
	 * @{
	 */
	/** @brief An efficient driver-specific representation of pixel data. */
	class VAS_DECLSPEC Texture
	{ /** @} */
	public:
		Texture(); /**< Create empty instance of texutre. */
		/**< Create new instance of texture. */
		Texture(Renderer& renderer, uint32_t format, int access, const Point& size);
		Texture(Renderer& renderer, Surface surface); /**< Create texture from surface. */
		/**
		 * Reference to a SDL_Texture.
		 * @param[in] other Raw instance of texture component.
		 * @param[in] owner Determine if instance is an owner of @p other.
		 */
		explicit Texture(SDL_Texture* other, bool owner = false);

		bool getAlphaMod(uint8_t* alpha); /**< Get alpha mod fo texture, or the opacity. @return true if success. */
		bool getBlendMod(BlendMode* mode); /**< Get blend mode of the texture. @return true if success. */
		bool getColorMod(uint8_t* red, uint8_t* green, uint8_t* bule); /**< Get colour mod of texture. @return true if success. */

		void loadImage(Renderer& renderer, const std::string& file); /**< Load from image file directy. */
		void loadImageRaw(Renderer& renderer, rwops::RWops* src, bool freeSrc = true); /**< Load image from memory directly. */

		/**
		 * Load an image from an SDL data source.
		 * The 'type' may be one of: "BMP", "GIF", "PNG", etc.
		 * 
		 * If the image format supports a transparent pixel, SDL will set the
		 * colorkey for the surface.  You can enable RLE acceleration on the
		 * surface afterwards by calling:
		 * SDL_SetColorKey(image, SDL_RLEACCEL, image->format->colorkey);
		 */
		void loadImageTypedRaw(Renderer& renderer, rwops::RWops* src, const std::string& type, bool freeSrc = true);
		bool lockTexture(const Rect& rect, void** pixels, int* pitch); /**< Lock the texture. @return true if success. */

		bool setAlphaMod(uint8_t alpha); /**< Set texture alpha mod. */
		bool setBlendMod(BlendMode mode); /**< Set texture blend mode. */
		bool setColorMod(uint8_t red, uint8_t green, uint8_t bule); /**< Set texture colour mod. */

		void unlockTexture(); /**< Unlock texture. */
		/**
		 * Update the texture.
		 * @return true if success.
		 * @note This is a fairly slow function
		 */
		bool updateTexture(const Rect& rect, const void* pixels, int pitch);
		/**
		 * Update texture YUV data.
		 * @return true if success.
		 */
		bool updateYUVTexture(const Rect& rect, const Uint8* Yplane, int Ypitch, const Uint8* Uplane, int Upitch, const Uint8* Vplane, int Vpitch);

		/**
		 * Get the size of the texture.
		 * @return true if success.
		 */
		bool queryTexture(int* w, int* h);
		/**
		 * Query texture.
		 * @return ture if success.
		 */
		bool queryTexture(uint32_t* format, int* access, int* w, int* h);
		void destroy(); /**< Destroy instance. */
		bool isNull(); /**< Check if this instance is null. */
		/**
		 * @name Overloaded operators
		 * @{
		 */
		explicit operator SDL_Texture*(); /**< Get raw component. */
		bool operator==(const Texture& rhs); /**< Determine if two instance are equal. */
		bool operator!=(const Texture& rhs); /**< Determine if two instance are not equal. */
		bool operator==(NullComponent_t); /**< Determine if this instance is null. */
		bool operator!=(NullComponent_t); /**< Determine if this instance is not null. */

		Texture& operator=(NullComponent_t); /** Destroy instance by assigning it to nullcomponent. */
		/** @} */
	private:
		std::shared_ptr<SDL_Texture> componentInstance;
	};
}