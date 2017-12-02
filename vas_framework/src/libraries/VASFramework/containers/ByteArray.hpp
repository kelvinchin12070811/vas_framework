/*****************************************************************************************

version 1.2.8, April 28th, 2013

Copyright (C) 2017 Kelvin Chin

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

******************************************************************************************/

#ifndef COM_BLOGSPOT_KELVINCHIN12070811_VAS_BYTEARRAY_H
#define COM_BLOGSPOT_KELVINCHIN12070811_VAS_BYTEARRAY_H
#include <vector>
#include <cstdint>

/***************************************************************************************************************

This is an alias name of std::vector<uint8_t> as ByteArray
Use to store binary data as an array of data

***************************************************************************************************************/

namespace vas
{
	using ByteArray = std::vector<uint8_t>;
}
#endif // !COM_BLOGSPOT_KELVINCHIN12070811_VAS_BYTEARRAY_H
