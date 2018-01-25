#include "Keycode.hpp"

bool sdl::operator==(SDL_Keycode lhs, Keycode rhs)
{
	return static_cast<Keycode>(lhs) == rhs;
}

bool sdl::operator==(Keycode lhs, SDL_Keycode rhs)
{
	return lhs == static_cast<Keycode>(rhs);
}

bool sdl::operator!=(SDL_Keycode lhs, Keycode rhs)
{
	return static_cast<Keycode>(lhs) != rhs;
}

bool sdl::operator!=(Keycode lhs, SDL_Keycode rhs)
{
	return lhs != static_cast<Keycode>(rhs);
}