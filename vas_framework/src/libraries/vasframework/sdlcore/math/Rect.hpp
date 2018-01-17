#pragma once
#include <SDL.h>

namespace sdl
{
	class Rect
	{
	public:
		Rect();
		Rect(int x, int y, int w, int h);
		explicit Rect(SDL_Rect rect);
		~Rect();
		int x = 0;
		int y = 0;
		int w = 0;
		int h = 0;

		operator SDL_Rect();
		operator const SDL_Rect() const;
	};
}