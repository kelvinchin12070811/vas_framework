#include "Property.hpp"

namespace vas
{
	Property::Property(const std::wstring& name, const std::wstring & value):
		name(name), value(value)
	{
	}

	Property::Property(const Property & other):
		name(other.name), value(other.value)
	{
	}

	Property::Property(Property && other):
		name(std::move(other.name)), value(std::move(other.value))
	{
	}

	Property::~Property()
	{
	}

	const std::wstring& Property::getRaw(const std::wstring& def) const
	{
		return value.empty() ? def : value;
	}

	const std::wstring & Property::getName() const
	{
		return name;
	}

	Property & Property::operator=(const Property & rhs)
	{
		this->name = rhs.name;
		this->value = rhs.value;
		return *this;
	}

	Property & Property::operator=(Property && rhs)
	{
		this->name = std::move(rhs.name);
		this->value = std::move(rhs.value);
		return *this;
	}
}