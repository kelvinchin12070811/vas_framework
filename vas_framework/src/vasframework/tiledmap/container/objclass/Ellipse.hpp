#pragma once
#if (__has_include(<pugixml/pugiconfig.hpp>) && __has_include(<zlib.h>)) || defined(DOXYGEN)
#include "IShape.hpp"
#include "../../../math/Vector2.hpp"

namespace vas
{
	/** @addtogroup tile_codec
		  @{
	*/
	/** @brief Ellipse shape object on map. */
	class Ellipse : public IShape
	{ /** @} */
	public:
		Vector2 position; /**< Position of object. */
		int width{ 0 }; /**< Width of ellipse. */
		int height{ 0 }; /**< Height of ellipse. */
	};
}
#endif // (__has_include(<pugixml/pugiconfig.hpp>) && __has_include(<zlib.h>)) || defined(DOXYGEN)
