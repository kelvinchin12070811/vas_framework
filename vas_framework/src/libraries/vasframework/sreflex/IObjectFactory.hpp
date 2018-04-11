#pragma once
#include <memory>
#include "IObjectEntries.hpp"

namespace vas
{
	namespace sreflex
	{
		class VAS_DECLSPEC IObjectFactory
		{
		public:
			IObjectFactory();
			~IObjectFactory();

			std::unique_ptr<IObject> createObject(const std::string& objName);
		};
	}
}