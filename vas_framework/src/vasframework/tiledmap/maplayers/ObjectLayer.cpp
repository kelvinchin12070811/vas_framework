//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#if (__has_include(<pugixml/pugiconfig.hpp>) && __has_include(<zlib.h>)) || defined(DOXYGEN)
#include "ObjectLayer.hpp"

namespace vas
{
	void ObjectLayer::setObjectList(std::vector<ObjectData>&& value)
	{
		objectList = std::move(value);
	}

	const std::vector<ObjectData>& ObjectLayer::getObjectList() const
	{
		return objectList;
	}
}
#endif // (__has_include(<pugixml/pugiconfig.hpp>) && __has_include(<zlib.h>)) || defined(DOXYGEN)
