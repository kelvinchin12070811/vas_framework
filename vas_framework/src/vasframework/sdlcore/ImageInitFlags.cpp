#include "ImageInitFlags.hpp"

namespace vas::sdl
{
	namespace image
	{
		const int ImageInitFlags::jpg = IMG_INIT_JPG;
		const int ImageInitFlags::png = IMG_INIT_PNG;
		const int ImageInitFlags::tif = IMG_INIT_TIF;
		const int ImageInitFlags::webp = IMG_INIT_WEBP;
		const int ImageInitFlags::all = ImageInitFlags::jpg | ImageInitFlags::png | ImageInitFlags::tif | ImageInitFlags::webp;
		const int ImageInitFlags::all_webp_not_included = ImageInitFlags::jpg | ImageInitFlags::png | ImageInitFlags::tif;
	}
}