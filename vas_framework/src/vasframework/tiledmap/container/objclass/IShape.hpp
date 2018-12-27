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
		IShape() = default;
		IShape(const IShape&) = default;
		IShape(IShape&&) = default;
		IShape& operator=(const IShape&) = default;
		IShape& operator=(IShape&&) = default;
		virtual ~IShape() = 0;
	};
	inline IShape::~IShape() = default;
}
#endif // (__has_include(<pugixml/pugiconfig.hpp>) && __has_include(<zlib.h>)) || defined(DOXYGEN)
