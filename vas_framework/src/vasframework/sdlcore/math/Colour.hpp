//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <SDL2/SDL.h>
#include "../../VASConfig.hpp"

namespace vas::sdl
{
	/**
	 * @ingroup sdl_basic
	 * @{
	 */
	/** @brief The container of RGBA colour. */
	class VAS_DECLSPEC Colour
	{
	public:
		Colour() = default; /**< Create empty colour. Default is black. */
		Colour(const Colour&) = default;
		Colour(Colour&&) = default;
		Colour& operator=(const Colour&) = default;
		Colour& operator=(Colour&&) = default;
		~Colour() {}
		/** Create colour from rgb or rgba value. */
		Colour(uint8_t red, uint8_t green, uint8_t bule, uint8_t alpha = 255);
		explicit Colour(SDL_Colour rhs); /**< Cast from SDL_Colour or SDL_Color. */

		bool operator==(const Colour& rhs) const;
		bool operator!=(const Colour& rhs) const;

		explicit operator SDL_Colour() const; /**< Cast to SDL_Colour or SDL_Color. */

		uint8_t red{ 0 }; /**< Red value. */
		uint8_t green{ 0 }; /**< Green value. */
		uint8_t bule{ 0 }; /**< Blue value. */
		uint8_t alpha{ 255 }; /**< Alpha value. */
	};

	/** @brief Collection of colour presets. */
	struct ColourPresets
	{
		static const Colour red; /**< Red */
		static const Colour green; /**< Green */
		static const Colour blue; /**< Blue */
		static const Colour black; /**< Black */
		static const Colour white; /**< White */
		static const Colour pink; /**< Pink */
		static const Colour hotPink; /**< Hot pink */
		static const Colour yellow; /**< Yellow */
		static const Colour purple; /**< Purple */
		static const Colour indigo; /**< Indigo */
		static const Colour brown; /**< Brown */
		static const Colour chocolate; /**< Chocolate */
		static const Colour orange; /**< Orange */
		static const Colour crimson; /**< Crimson */
		static const Colour grey; /**< Grey */
		static const Colour maroon; /**< Maroon */
		static const Colour cyan; /**< Cyan */
		static const Colour magenta; /**< Magenta */
		static const Colour cc5004b7;
	};

	using Color = Colour; /**< Typedef for NAME english varian. */
	using ColorPresets = ColourPresets; /**< Typedef for NAME english varian. */

	/** @} */
}