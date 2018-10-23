#pragma once
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