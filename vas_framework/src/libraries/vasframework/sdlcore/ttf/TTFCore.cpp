#include "TTFCore.hpp"

bool sdl::ttf::init()
{
	return TTF_Init() == 0;
}
