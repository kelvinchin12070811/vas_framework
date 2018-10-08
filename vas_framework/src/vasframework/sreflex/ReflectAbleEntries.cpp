#include "ReflectAbleEntries.hpp"

namespace vas
{
	namespace sreflex
	{
		ReflectAbleEntries & ReflectAbleEntries::getInstance()
		{
			static ReflectAbleEntries instance;
			return instance;
		}

		std::unique_ptr<ReflectAbleEntries::ObjectMap> & ReflectAbleEntries::getRegistry()
		{
			return registry;
		}

		bool ReflectAbleEntries::registerInstance(const std::string & objName, ReflectAbleCreateFunction creator)
		{
			auto result = registry->insert(std::make_pair(objName, creator));
			return result.second;
		}

		ReflectAbleEntries::ReflectAbleEntries()
		{
			registry = std::make_unique<ReflectAbleEntries::ObjectMap>();
		}

		ReflectAbleEntries::~ReflectAbleEntries()
		{
		}
	}
}