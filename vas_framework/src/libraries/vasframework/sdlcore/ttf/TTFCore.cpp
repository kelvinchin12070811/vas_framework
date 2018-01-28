#include "TTFCore.hpp"

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
