#pragma once
#include <string>
#include "../../VASConfig.hpp"

namespace vas
{
	class AbstractMapLayer
	{
	public:
		AbstractMapLayer();
		virtual ~AbstractMapLayer() = 0;

		virtual std::string getName() const;
		virtual void setName(const std::string& name);
	protected:
		std::string name;
	};
}