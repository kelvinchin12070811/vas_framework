#pragma once
#include <map>
#include <memory>
#include <string>
#include <functional>
#include "IObject.hpp"

#define SREFLEX_VAR_NAME(x) std::string(#x)

namespace sreflex
{
	using IObjectCreatefunction = IObject*(*)();

	template <typename IObjectType>
	IObject* createObjectBase()
	{
		return new IObjectType();
	}

	class IObjectFactory
	{
	public:
		IObjectFactory();
		~IObjectFactory();

		IObject* createObjectPointer(const std::string& objectName);
		std::shared_ptr<IObject> createObject(const std::string& objectName);

		static std::map<std::string, IObjectCreatefunction>* getMap();
	private:
		static std::map<std::string, IObjectCreatefunction>* instanceMap;
	};

	bool __registerInstance(const std::string& name, IObjectCreatefunction function);
}

#define SREFLEX_REGISTER_INSTANCE(instance) sreflex::__registerInstance(#instance, &sreflex::createObjectBase<instance>)