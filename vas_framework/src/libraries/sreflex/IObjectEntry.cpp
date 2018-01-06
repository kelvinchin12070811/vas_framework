#include "IObjectEntry.hpp"

namespace sreflex
{
	IObjectEntry & IObjectEntry::getInstance()
	{
		static IObjectEntry instance;
		return instance;
	}

	std::map<std::string, IObjectCreatefunction>* IObjectEntry::getMap()
	{
		return this->objectsMap;
	}

	IObjectEntry::IObjectEntry()
	{
		if (objectsMap == nullptr)
			objectsMap = new std::map<std::string, IObjectCreatefunction>;
	}


	IObjectEntry::~IObjectEntry()
	{
		if (objectsMap != nullptr)
			delete objectsMap;
	}
}
