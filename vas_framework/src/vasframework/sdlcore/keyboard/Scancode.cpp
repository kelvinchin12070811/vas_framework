//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "Scancode.hpp"

namespace vas::sdl
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