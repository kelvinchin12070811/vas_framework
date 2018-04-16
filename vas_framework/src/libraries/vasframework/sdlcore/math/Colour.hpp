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

	struct ColourPresets
	{
		static const Colour red;
		static const Colour green;
		static const Colour blue;
		static const Colour black;
		static const Colour white;
		static const Colour pink;
		static const Colour hotPink;
		static const Colour yellow;
		static const Colour purple;
		static const Colour indigo;
		static const Colour brown;
		static const Colour chocolate;
		static const Colour orange;
		static const Colour crimson;
		static const Colour grey;
		static const Colour maroon;
		static const Colour cyan;
		static const Colour magenta;
		static const Colour cc5004b7;
	};
	using Color = Colour;
	using ColorPresets = ColourPresets;
}