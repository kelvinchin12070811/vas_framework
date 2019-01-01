//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "PropertyList.hpp"

namespace vas
{
	PropertyList::PropertyList()
	{
	}

	PropertyList::PropertyList(const PropertyList & rhs):
		super(rhs)
	{
	}

	PropertyList::PropertyList(PropertyList && rhs) noexcept :
		super(std::move(rhs))
	{
	}

	PropertyList::PropertyList(std::initializer_list<Property> list):
		super(list)
	{
	}

	PropertyList::~PropertyList()
	{
	}

	Property & PropertyList::find(const std::string & name)
	{
		return const_cast<Property&>(const_cast<const PropertyList*>(this)->find(name));
	}

	const Property & PropertyList::find(const std::string & name) const
	{
		auto result = std::find_if(this->begin(), this->end(), [&](const Property& itr)-> bool
		{
			return itr.getName() == name;
		});

		if (result == this->end()) throw std::out_of_range{ "cannot find property \"" + name + "\"" };
		return *result;
	}

	PropertyList & PropertyList::operator=(PropertyList && rhs) noexcept
	{
		super::operator=(std::move(rhs));
		return *this;
	}

	PropertyList & PropertyList::operator=(std::initializer_list<Property> list)
	{
		super::operator=(list);
		return *this;
	}

	Property & PropertyList::operator[](const std::string & name)
	{
		return find(name);
	}

	const Property & PropertyList::operator[](const std::string & name) const
	{
		return find(name);
	}
	Property & PropertyList::operator[](size_t index)
	{
		return super::operator[](index);
	}

	const Property & PropertyList::operator[](size_t index) const
	{
		return super::operator[](index);
	}
}