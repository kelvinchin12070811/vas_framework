//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#if (__has_include(<pugixml/pugiconfig.hpp>) && __has_include(<zlib.h>)) || defined(DOXYGEN)
#include <string>
#include "../../VASConfig.hpp"
#include "../../container/PropertyList.hpp"

namespace vas
{
	/** @ingroup tile_codec
		  @{
	*/
	/** @brief The basic interface of map layers. */
	class VAS_DECLSPEC AbstractMapLayer
	{ /** @} */
	public:
		AbstractMapLayer() = default;
		AbstractMapLayer(const AbstractMapLayer&) = default;
		AbstractMapLayer(AbstractMapLayer&&) noexcept = default;
		AbstractMapLayer& operator=(const AbstractMapLayer&) = default;
		AbstractMapLayer& operator=(AbstractMapLayer&&) noexcept = default;
		virtual ~AbstractMapLayer() = 0;

		virtual std::string getName() const;
		virtual void setName(const std::string& name);

		virtual const PropertyList& getProperties() const;
		virtual void setProperties(PropertyList&& value);
	protected:
		/** [Read & Write] The name of the map layer.\n
				- __mutators__
					-# virtual void setName(const std::string& name)
				- __accessors__
					-# virtual std::string getName() const
		*/
		std::string name;
		/** [Read & Write] The properties of the map layer.\n
				- __mutators__
					-# virtual void setProperties(PropertyList&& value)
				- __accessors__
					-# virtual const PropertyList& getProperties() const
		*/
		PropertyList properties;
	};

	inline AbstractMapLayer::~AbstractMapLayer() = default;
}
#endif // (__has_include(<pugixml/pugiconfig.hpp>) && __has_include(<zlib.h>)) || defined(DOXYGEN)
