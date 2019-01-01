//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include "ReflectAbleEntries.hpp"

namespace vas
{
	namespace sreflex
	{
		/*! \addtogroup sreflex
			 @{
		*/
		/*! \brief The class that automaticaly register a child of vas::sreflex::ReflectAble.

			 ReflectAbleAutoRegistrar is a utility that help user to register a child of vas::sreflex::ReflectAble. This class operate by
			 creating a static instance of it self with the name of the object.

			 @tparam ObjectType Object that need to register. It must be a child of ReflectAble.
		*/
		template<typename ObjectType>
		class ReflectAbleAutoRegistrar
		{
		public:
			/*! Register a new object with object's name
				 \param objName Object name.
			*/
			ReflectAbleAutoRegistrar(const std::string& objName)
			{
				ReflectAbleEntries::getInstance().registerInstance(objName, &vas::sreflex::createObjectBase<ObjectType>);
			}

			/*! Register a new object and the object name is searched automaticaly */
			ReflectAbleAutoRegistrar()
			{
				ReflectAbleEntries::getInstance().registerInstance(getObjectName<ObjectType>(), &vas::sreflex::createObjectBase<ObjectType>);
			}
		};
		/*! @} */
	}
}