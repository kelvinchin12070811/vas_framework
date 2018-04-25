#pragma once
#include "IObjectEntries.hpp"

namespace vas
{
	namespace sreflex
	{
		template<typename ObjectType>
		class IObjectAutoRegistrar
		{
		public:
			IObjectAutoRegistrar(const std::string& objName)
			{
				IObjectEntries::getInstance().registerInstance(objName, &vas::sreflex::createObjectBase<ObjectType>);
			}

			IObjectAutoRegistrar()
			{
				IObjectEntries::getInstance().registerInstance(getObjectName<ObjectType>(), &vas::sreflex::createObjectBase<ObjectType>);
			}
		};
	}
}