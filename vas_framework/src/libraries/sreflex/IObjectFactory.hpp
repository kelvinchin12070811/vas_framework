#pragma once
#include <map>
#include <memory>
#include <string>
#include "IObjectEntry.hpp"

#define SREFLEX_VAR_NAME(x) std::string(#x)

namespace sreflex
{


	class IObjectFactory
	{
	public:
		IObjectFactory();
		~IObjectFactory();

		IObject* createObjectPointer(const std::string& objectName);
		std::shared_ptr<IObject> createObject(const std::string& objectName);
	};

	bool __registerInstance(const std::string& name, IObjectCreatefunction function);
}

#define SREFLEX_REGISTER_INSTANCE(instance) sreflex::__registerInstance(#instance, &sreflex::createObjectBase<instance>)