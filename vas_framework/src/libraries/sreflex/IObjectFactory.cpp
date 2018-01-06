#include "IObjectFactory.hpp"
#include <exception>

namespace sreflex
{
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
			return IObjectEntryAPI().getMap()->at(objectName)();
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

	bool __registerInstance(const std::string & name, IObjectCreatefunction function)
	{
		auto result = sreflex::IObjectEntryAPI().getMap()->insert(std::make_pair(name, function));
		return result.second;
	}
}