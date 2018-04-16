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

	const Colour ColourPresets::red = Colour(0xff, 0x00, 0x00);
	const Colour ColourPresets::green = Colour(0x00, 0xff, 0x00);
	const Colour ColourPresets::blue = Colour(0x00, 0x00, 0xff);
	const Colour ColourPresets::black = Colour(0x00, 0x00, 0x00);
	const Colour ColourPresets::white = Colour(0xff, 0xff, 0xff);
	const Colour ColourPresets::pink = Colour(0xff, 0x96, 0xca);
	const Colour ColourPresets::hotPink = Colour(0xff, 0x69, 0xb4);
	const Colour ColourPresets::yellow = Colour(0xff, 0xff, 0x00);
	const Colour ColourPresets::purple = Colour(0x80, 0x00, 0x80);
	const Colour ColourPresets::indigo = Colour(0x4b, 0x00, 0x82);
	const Colour ColourPresets::brown = Colour(0xa5, 0x2a, 0x2a);
	const Colour ColourPresets::chocolate = Colour(0xd2, 0x69, 0x1e);
	const Colour ColourPresets::orange = Colour(0xff, 0xa5, 0x00);
	const Colour ColourPresets::crimson = Colour(0xdc, 0x14, 0x3c);
	const Colour ColourPresets::grey = Colour(0x80, 0x80, 0x80);
	const Colour ColourPresets::maroon = Colour(0x80, 0x00, 0x00);
	const Colour ColourPresets::cyan = Colour(0x00, 0xff, 0xff);
	const Colour ColourPresets::magenta = Colour(0xff, 0x00, 0xff);
	const Colour ColourPresets::cc5004b7 = Colour(0xcc, 0x50, 0x04, 0xb7);
}