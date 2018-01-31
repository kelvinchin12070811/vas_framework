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

		IObject * IObjectFactory::createObjectRaw(const std::string & objName)
		{
			try
			{
				return IObjectEntries::getInstance().getRegistry()->at(objName)();
			}
			catch (const std::exception&)
			{
				return nullptr;
			}
		}

		std::shared_ptr<IObject> IObjectFactory::createObject(const std::string & objName)
		{
			return std::shared_ptr<IObject>(createObjectRaw(objName));
		}
	}
}