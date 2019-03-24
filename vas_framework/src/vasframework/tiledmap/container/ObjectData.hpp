//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#if (__has_include(<pugixml/pugiconfig.hpp>) && __has_include(<zlib.h>)) || defined(DOXYGEN)
#include <memory>
#include <string>
#include "../../math/Vector2.hpp"
#include "../../container/PropertyList.hpp"
#include "objclass/IShape.hpp"

namespace vas
{
	/** @ingroup tile_codec
		  @{
	*/
	/** @brief Object to draw on ObjectLayer.

		  The information about object that will be display on the ObjectLayer.
	*/
	struct ObjectData
	{ /** @} */
		std::string name; /**< Name of the object. */
		std::string type; /**< Type of the object. */
		std::unique_ptr<IShape> instance; /**< The instance of the object's metadatas. */
		PropertyList properties; /**< Properties of the object. */
	};
}
#endif // (__has_include(<pugixml/pugiconfig.hpp>) && __has_include(<zlib.h>)) || defined(DOXYGEN)
