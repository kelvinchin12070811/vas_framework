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