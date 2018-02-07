#pragma once
#include <SDL.h>
#include "../../VASConfig.hpp"

namespace sdl
{
	class VAS_DECLSPEC Colour
	{
	public:
		Colour();
		Colour(uint8_t red, uint8_t green, uint8_t bule, uint8_t alpha = 255);
		explicit Colour(SDL_Colour rhs);
		~Colour();

		bool operator==(const Colour& rhs) const;
		bool operator!=(const Colour& rhs) const;

		explicit operator SDL_Colour() const;

		uint8_t red{ 0 };
		uint8_t green{ 0 };
		uint8_t bule{ 0 };
		uint8_t alpha{ 255 };
	};

	using Color = Colour;
}