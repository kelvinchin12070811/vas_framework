//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "TTFCore.hpp"

#ifdef VAS_USE_TTF
namespace vas
{
	bool sdl::ttf::init()
	{
		return TTF_Init() == 0;
	}

	void sdl::ttf::quit()
	{
		TTF_Quit();
	}

	bool sdl::ttf::wasInit()
	{
		return TTF_WasInit() == 1;
	}
}
#endif // VAS_USE_TTF