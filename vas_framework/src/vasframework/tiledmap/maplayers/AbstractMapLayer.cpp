#if (__has_include(<pugixml/pugiconfig.hpp>) && __has_include(<zlib.h>)) || defined(DOXYGEN)
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
#endif // (__has_include(<pugixml/pugiconfig.hpp>) && __has_include(<zlib.h>)) || defined(DOXYGEN)
