#include "IObjectEntries.hpp"

namespace vas
{
	namespace sreflex
	{
		IObjectEntries & IObjectEntries::getInstance()
		{
			static IObjectEntries instance;
			return instance;
		}

		std::unique_ptr<IObjectEntries::ObjectMap> & IObjectEntries::getRegistry()
		{
			return registry;
		}

		bool IObjectEntries::registerInstance(const std::string & objName, IObjectCreateFunction creator)
		{
			auto result = registry->insert(std::make_pair(objName, creator));
			return result.second;
		}

		IObjectEntries::IObjectEntries()
		{
			registry = std::make_unique<IObjectEntries::ObjectMap>();
		}

		IObjectEntries::~IObjectEntries()
		{
		}
	}
}