#include "Rect.hpp"

namespace sdl
{
	Rect::Rect()
	{
	}

	Rect::Rect(int x, int y, int w, int h):
		x(x), y(y), w(w), h(h)
	{
	}

	Rect::Rect(SDL_Rect rect):
		x(rect.x), y(rect.y), w(rect.w), h(rect.h)
	{
	}

	Rect::~Rect()
	{
	}

	Rect::operator SDL_Rect()
	{
		return SDL_Rect{ x, y, w, h };
	}

	Rect::operator const SDL_Rect() const
	{
		return SDL_Rect{ x, y, w, h };
	}
}