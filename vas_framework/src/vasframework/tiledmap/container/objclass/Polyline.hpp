#pragma once
#if (__has_include(<pugixml/pugiconfig.hpp>) && __has_include(<zlib.h>)) || defined(DOXYGEN)
#include <vector>
#include "IShape.hpp"
#include "../../../math/Vector2.hpp"

namespace vas
{
	/** @addtogroup tile_codec
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
