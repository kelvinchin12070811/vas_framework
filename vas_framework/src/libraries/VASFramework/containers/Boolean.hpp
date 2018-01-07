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

#ifndef COM_BLOGSPOT_KELVINCHIN12070811_VAS_BOOLEAN_H
#define COM_BLOGSPOT_KELVINCHIN12070811_VAS_BOOLEAN_H

#define VAS_BOOLEAN_GENDLL

namespace vas
{
#ifdef VAS_BOOLEAN_GENDLL
	class __declspec(dllexport) Boolean
#else
	class Boolean
#endif // VAS_BOOLEAN_GENDLL
	{
	public:
		Boolean();
		Boolean(const Boolean& rhs);
		Boolean(Boolean&& rhs);
		Boolean(const bool& rhs);
		Boolean(bool&& rhs);
		~Boolean();

		Boolean& operator=(const Boolean& rhs);
		Boolean& operator=(Boolean&& rhs);
		Boolean& operator=(const bool& rhs);
		Boolean& operator=(bool&& rhs);

		operator const bool&() const;
		operator bool&();

		bool operator==(const Boolean& rhs) const;
		bool operator!=(const Boolean& rhs) const;
		bool operator==(const bool& rhs) const;
		bool operator!=(const bool& rhs) const;
	private:
		bool value = false;
	};
}
#endif // !COM_BLOGSPOT_KELVINCHIN12070811_VAS_BOOLEAN