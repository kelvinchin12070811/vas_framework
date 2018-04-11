#include "IObjectFactory.hpp"

namespace vas
{
	namespace sreflex
	{
		IObjectFactory::IObjectFactory()
		{
		}

		IObjectFactory::~IObjectFactory()
		{
		}

		std::unique_ptr<IObject> IObjectFactory::createObject(const std::string & objName)
		{
			return IObjectEntries::getInstance().getRegistry()->at(objName)();
		}
	}
}