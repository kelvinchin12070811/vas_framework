#pragma once
#include <map>
#include <string>
#include "IObject.hpp"

namespace sreflex
{
	using IObjectCreatefunction = IObject*(*)();

	template <typename IObjectType>
	IObject* createObjectBase()
	{
		return new IObjectType();
	}

	class SREFLEX_DLLEXPORT IObjectEntry
	{
	public:
		static IObjectEntry& getInstance();

		std::map<std::string, IObjectCreatefunction>* getMap();
	private:
		IObjectEntry();
		~IObjectEntry();

		std::map<std::string, IObjectCreatefunction>* objectsMap = nullptr;
	};

	inline IObjectEntry& IObjectEntryAPI() { return sreflex::IObjectEntry::getInstance(); };
}