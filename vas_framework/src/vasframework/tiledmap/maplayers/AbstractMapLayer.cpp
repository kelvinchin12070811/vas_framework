//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#if (__has_include(<pugixml/pugiconfig.hpp>) && __has_include(<zlib.h>)) || defined(DOXYGEN)
#include "AbstractMapLayer.hpp"

namespace vas
{
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
