#pragma once

#if (__has_include(<pugixml/pugiconfig.hpp>) && __has_include(<zlib.h>)) || defined(DOXYGEN)
namespace vas
{
	/** @addtogroup tile_codec
		  @{
	*/
	/** @brief Basic shape object interface. */
	class IShape
	{ /** @} */
	public:
		IShape() {}
		virtual ~IShape() = 0 {}
	};
}
#endif // (__has_include(<pugixml/pugiconfig.hpp>) && __has_include(<zlib.h>)) || defined(DOXYGEN)
