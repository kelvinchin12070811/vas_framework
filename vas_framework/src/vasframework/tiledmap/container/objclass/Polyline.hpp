//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#if (__has_include(<pugixml/pugiconfig.hpp>) && __has_include(<zlib.h>)) || defined(DOXYGEN)
#include <vector>
#include "IShape.hpp"
#include "../../../math/Vector2.hpp"

namespace vas
{
	/** @ingroup tile_codec
		  @{
	*/
	/** @brief Polyine object on map. */
	class Polyline : public IShape
	{ /** @} */
	public:
		Vector2 position; /**< Position of the line. */
		std::vector<Vector2> line; /**< Point of the line from the position of the line. */
	};
}
#endif // (__has_include(<pugixml/pugiconfig.hpp>) && __has_include(<zlib.h>)) || defined(DOXYGEN)
