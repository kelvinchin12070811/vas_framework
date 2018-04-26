#include "Property.hpp"

namespace vas
{
	Property::Property()
	{
	}

	Property::Property(const std::string& name, const boost::any & value):
		name(name), value(value)
	{
	}

	Property::Property(const std::string& name, boost::any && value):
		name(name), value(std::move(value))
	{
	}

	Property::Property(const Property & rhs):
		name(rhs.name), value(rhs.value)
	{
	}

	Property::Property(Property && rhs):
		name(std::move(rhs.name)), value(std::move(rhs.value))
	{
	}

	Property::~Property()
	{
	}

	const boost::typeindex::type_index Property::type() const
	{
		return value.type();
	}

	bool Property::empty() const
	{
		return value.empty();
	}

	void Property::swap(Property & rhs)
	{
		name.swap(rhs.name);
		value.swap(rhs.value);
	}

	void Property::clear()
	{
		value.clear();
	}

	Property::operator boost::any&()
	{
		return const_cast<boost::any&>(operator const boost::any &());
	}

	Property::operator const boost::any&() const
	{
		return value;
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

	Property & Property::operator=(const boost::any & rhs)
	{
		this->value = rhs;
		return *this;
	}

	Property & Property::operator=(boost::any && rhs)
	{
		this->value = std::move(rhs);
		return *this;
	}
}