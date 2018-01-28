#include "Colour.hpp"

namespace sdl
{
	Colour::Colour()
	{
	}

	Colour::Colour(uint8_t red, uint8_t green, uint8_t bule, uint8_t alpha):
		red(red), green(green), bule(bule), alpha(alpha)
	{
	}

	Colour::Colour(SDL_Colour rhs):
		red(rhs.r), green(rhs.g), bule(rhs.b), alpha(rhs.a)
	{
	}

	Colour::~Colour()
	{
	}

	bool Colour::operator==(const Colour & rhs) const
	{
		return (red == rhs.red) && (green == rhs.green) && (bule == rhs.bule) && (alpha == rhs.alpha);
	}

	bool Colour::operator!=(const Colour & rhs) const
	{
		return (red != rhs.red) || (green != rhs.green) || (bule != rhs.bule) || (alpha != rhs.alpha);
	}

	Colour::operator SDL_Colour() const
	{
		SDL_Colour instance = { red, green, bule, alpha };
		return instance;
	}
}