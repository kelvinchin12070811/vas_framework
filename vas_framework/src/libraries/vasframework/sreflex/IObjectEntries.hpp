#pragma once
#include <map>
#include <memory>
#include "IObject.hpp"

#define SREFLEX_OBJ_NAME(obj) std::string(#obj)

namespace vas
{
	namespace sreflex
	{
		using IObjectCreateFunction = IObject* (*)();
		template <typename IObjectType>
		IObject* createObjectBase()
		{
			return new IObjectType();
		}

		class VAS_DECLSPEC IObjectEntries
		{
		public:
			using ObjectMap = std::map<std::string, IObjectCreateFunction>;

			static IObjectEntries& getInstance();

			std::unique_ptr<ObjectMap>& getRegistry();
			bool registerInstance(const std::string& objName, IObjectCreateFunction creator);
		private:
			IObjectEntries();
			~IObjectEntries();

			std::unique_ptr<ObjectMap> registry{ nullptr };
		};
	}
}