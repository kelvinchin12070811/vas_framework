#include "TTFCore.hpp"

#ifdef VAS_USE_TTF
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
#endif // VAS_USE_TTF