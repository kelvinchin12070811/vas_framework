//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "Keycode.hpp"

namespace vas
{
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
}