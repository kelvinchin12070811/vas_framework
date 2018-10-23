#pragma once
#include "IShape.hpp"
#include "../../../math/Vector2.hpp"

namespace vas
{
	/** @addtogroup tile_codec
		  @{
	*/
	/** @brief Rectangle object on map. */
	class Rectangle : public IShape
	{ /** @} */
	public:
		Vector2 position; /**< Position of the object. */
		int width{ 0 }; /**< Width of the rectangle. */
		int height{ 0 }; /**< Height of the rectangle. */
	};
}