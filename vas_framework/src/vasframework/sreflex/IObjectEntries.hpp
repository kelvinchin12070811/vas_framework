#pragma once
#include <map>
#include <memory>
#include "IObject.hpp"
#include "Util.hpp"

namespace vas
{
	namespace sreflex
	{
		/** @addtogroup sreflex
			 @{
		*/

		/** Creator function of children of IObject

			 Defined in: vasframework/sreflex/IObjectEntries.hpp
		*/
		using IObjectCreateFunction = std::unique_ptr<IObject> (*)();

		/** Default creator function of IObject's children
			 
			 @tparam IObjectType Object that need to be created. It must be a child of IObject.

			 Defined in: vasframework/sreflex/IObjectEntries.hpp
		*/
		template <typename IObjectType>
		std::unique_ptr<IObject> createObjectBase()
		{
			return std::make_unique<IObjectType>();
		}

		/** @brief Registry class that maps IObject's children name to their creator function.
			 
			 | Header | Namespace |
			 | : --- : | : --- : |
			 | vasframework/sreflex/IObjectEntries.hpp | vas::sreflex |

			  This is the singletone class that store key-value pair of IObject children with its' creator function.
		*/
		class VAS_DECLSPEC IObjectEntries
		{
		public:
			using ObjectMap = std::map<std::string, IObjectCreateFunction>;/**< Registry that store key to value mapping
																		   to the IObject children and its creator function*/

			/** Return the singletone instance of IObjectEntries
			*/
			static IObjectEntries& getInstance();

			std::unique_ptr<ObjectMap>& getRegistry();

			/** Register an instance of IObject child*/
			bool registerInstance(const std::string& objName, IObjectCreateFunction creator);
		private:
			IObjectEntries();
			~IObjectEntries();

			std::unique_ptr<ObjectMap> registry{ nullptr }; /**< [Read Only] Registry that store data
																about all instance of IObject
																- accessor
																	-# std::unique_ptr<ObjectMap>& getRegistry()
															*/
		};

		/** @} */
	}
}