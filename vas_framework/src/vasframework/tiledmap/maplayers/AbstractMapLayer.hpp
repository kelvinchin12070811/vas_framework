#pragma once
#include <string>
#include "../../VASConfig.hpp"
#include "../../container/PropertyList.hpp"

namespace vas
{
	class VAS_DECLSPEC AbstractMapLayer
	{
	public:
		AbstractMapLayer();
		virtual ~AbstractMapLayer() = 0;

		virtual std::string getName() const;
		virtual void setName(const std::string& name);

		virtual const PropertyList& getProperties() const;
		virtual void setProperties(PropertyList&& value);
	protected:
		std::string name;
		PropertyList properties;
	};
}