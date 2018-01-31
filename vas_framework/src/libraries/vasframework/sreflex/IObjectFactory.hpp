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

			IObject* createObjectRaw(const std::string& objName);
			std::shared_ptr<IObject> createObject(const std::string& objName);
		};
	}
}