#pragma once
#include "IObjectEntries.hpp"

namespace vas
{
	namespace sreflex
	{
		/*! \addtogroup sreflex
			 @{
		*/
		/*! \brief The class that automaticaly register a child of vas::sreflex::IObject.

			 IObjectAutoRegistrar is a utility that help user to register a child of vas::sreflex::IObject. This class operate by
			 creating a static instance of it self with the name of the object.

			 @tparam ObjectType Object that need to register. It must be a child of IObject.
		*/
		template<typename ObjectType>
		class IObjectAutoRegistrar
		{
		public:
			/*! Register a new object with object's name
				 \param objName Object name.
			*/
			IObjectAutoRegistrar(const std::string& objName)
			{
				IObjectEntries::getInstance().registerInstance(objName, &vas::sreflex::createObjectBase<ObjectType>);
			}

			/*! Register a new object and the object name is searched automaticaly */
			IObjectAutoRegistrar()
			{
				IObjectEntries::getInstance().registerInstance(getObjectName<ObjectType>(), &vas::sreflex::createObjectBase<ObjectType>);
			}
		};
		/*! @} */
	}
}