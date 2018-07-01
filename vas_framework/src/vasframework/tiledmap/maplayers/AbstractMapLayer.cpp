#include "AbstractMapLayer.hpp"

namespace vas
{
	AbstractMapLayer::AbstractMapLayer()
	{
	}

	AbstractMapLayer::~AbstractMapLayer()
	{
	}

	std::string AbstractMapLayer::getName() const
	{
		return name;
	}

	void AbstractMapLayer::setName(const std::string & name)
	{
		this->name = name;
	}

	const PropertyList & AbstractMapLayer::getProperties() const
	{
		return properties;
	}

	void AbstractMapLayer::setProperties(PropertyList && value)
	{
		properties = std::move(value);
	}
}