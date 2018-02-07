#include "Property.hpp"

namespace vas
{
	Property::Property()
	{
	}

	Property::Property(const boost::any & value):
		value(value)
	{
	}

	Property::Property(boost::any && value):
		value(std::move(value))
	{
	}

	Property::Property(const Property & rhs):
		value(rhs.value)
	{
	}

	Property::Property(Property && rhs):
		value(std::move(rhs.value))
	{
	}

	Property::~Property()
	{
	}

	const std::type_info & Property::type() const
	{
		return value.type();
	}

	bool Property::empty() const
	{
		return value.empty();
	}

	void Property::swap(Property & rhs)
	{
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
		this->value = rhs.value;
		return *this;
	}

	Property & Property::operator=(Property && rhs)
	{
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