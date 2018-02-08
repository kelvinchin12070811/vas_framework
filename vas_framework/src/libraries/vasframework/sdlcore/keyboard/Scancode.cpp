#include "Scancode.hpp"

namespace sdl
{
	bool VAS_DECLSPEC operator==(SDL_Scancode lhs, Scancode rhs)
	{
		return static_cast<Scancode>(lhs) == rhs;
	}

	bool VAS_DECLSPEC operator==(Scancode lhs, SDL_Scancode rhs)
	{
		return lhs == static_cast<Scancode>(rhs);
	}

	bool VAS_DECLSPEC operator!=(SDL_Scancode lhs, Scancode rhs)
	{
		return static_cast<Scancode>(lhs) != rhs;
	}

	bool VAS_DECLSPEC operator!=(Scancode lhs, SDL_Scancode rhs)
	{
		return lhs != static_cast<Scancode>(rhs);
	}
}