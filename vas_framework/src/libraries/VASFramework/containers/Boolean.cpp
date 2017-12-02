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
#include "Boolean.hpp"
#include <algorithm>

namespace vas
{
	Boolean::Boolean()
	{
	}

	Boolean::Boolean(const Boolean & rhs):
		value(rhs.value)
	{
	}

	Boolean::Boolean(Boolean && rhs):
		value(std::move(rhs.value))
	{
	}

	Boolean::Boolean(const bool & rhs):
		value(rhs)
	{
	}

	Boolean::Boolean(bool && rhs):
		value(std::move(rhs))
	{
	}

	Boolean::~Boolean()
	{
	}

	Boolean & Boolean::operator=(const Boolean & rhs)
	{
		this->value = rhs.value;
		return *this;
	}

	Boolean & Boolean::operator=(Boolean && rhs)
	{
		this->value = std::move(rhs.value);
		return *this;
	}

	Boolean & Boolean::operator=(const bool & rhs)
	{
		this->value = rhs;
		return *this;
	}

	Boolean & Boolean::operator=(bool && rhs)
	{
		this->value = std::move(rhs);
		return *this;
	}

	Boolean::operator const bool&() const
	{
		return value;
	}

	Boolean::operator bool&()
	{
		return value;
	}

	bool Boolean::operator==(const Boolean & rhs) const
	{
		return this->value == rhs.value;
	}

	bool Boolean::operator!=(const Boolean & rhs) const
	{
		return this->value != rhs.value;
	}

	bool Boolean::operator==(const bool & rhs) const
	{
		return this->value == rhs;
	}

	bool Boolean::operator!=(const bool & rhs) const
	{
		return this->value != rhs;
	}
}