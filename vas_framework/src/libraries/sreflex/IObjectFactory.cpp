#include "IObjectFactory.hpp"
#include <exception>

namespace sreflex
{
	std::map<std::string, IObjectCreatefunction>* IObjectFactory::instanceMap = nullptr;

	IObjectFactory::IObjectFactory()
	{
	}


	IObjectFactory::~IObjectFactory()
	{
	}

	IObject * IObjectFactory::createObjectPointer(const std::string & objectName)
	{
		try
		{
			return instanceMap->at(objectName)();
		}
		catch (const std::exception&)
		{
			return nullptr;
		}
	}

	std::shared_ptr<IObject> IObjectFactory::createObject(const std::string & objectName)
	{
		return std::shared_ptr<IObject>(createObjectPointer(objectName));
	}

	std::map<std::string, IObjectCreatefunction>* IObjectFactory::getMap()
	{
		if (instanceMap == nullptr) instanceMap = new std::map<std::string, IObjectCreatefunction>;
		return instanceMap;
	}

	bool __registerInstance(const std::string & name, IObjectCreatefunction function)
	{
		auto result = sreflex::IObjectFactory::getMap()->insert(std::make_pair(name, function));
		return result.second;
	}
}