#pragma once
#include <map>
#include <memory>
#include "IObject.hpp"
#include "Util.hpp"

namespace vas
{
	namespace sreflex
	{
		using IObjectCreateFunction = std::unique_ptr<IObject> (*)();
		template <typename IObjectType>
		std::unique_ptr<IObject> createObjectBase()
		{
			return std::make_unique<IObjectType>();
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