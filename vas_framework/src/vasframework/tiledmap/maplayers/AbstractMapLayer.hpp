#pragma once
#include <string>
#include "../../VASConfig.hpp"
#include "../../container/PropertyList.hpp"

namespace vas
{
	/** @addtogroup tile_codec
		  @{
	*/
	/** @brief The basic interface of map layers. */
	class VAS_DECLSPEC AbstractMapLayer
	{ /** @} */
	public:
		AbstractMapLayer();
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
}