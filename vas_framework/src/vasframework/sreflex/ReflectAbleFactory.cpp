//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "ReflectAbleFactory.hpp"

namespace vas
{
	namespace sreflex
	{
		std::unique_ptr<ReflectAble> ReflectAbleFactory::createObject(const std::string & objName)
		{
			try
			{
				return ReflectAbleEntries::getInstance().getRegistry()->at(objName)();
			}
			catch (const std::out_of_range&)
			{
				return nullptr;
			}
		}
	}
}