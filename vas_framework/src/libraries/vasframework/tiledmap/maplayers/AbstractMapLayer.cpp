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
}