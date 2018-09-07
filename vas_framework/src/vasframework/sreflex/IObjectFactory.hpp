#pragma once
#include <memory>
#include "IObjectEntries.hpp"

namespace vas
{
	namespace sreflex
	{
		/** @addtogroup sreflex
			  @{
		*/
		/** @brief The factory class that create IObject instance with their name
			  
			  | Header | Namespace |
			  | : --- : | : --- : |
			  | vasframework/sreflex/IObjectFactory.hpp | vas::sreflex |

			  IObjectFactory class create and return the instance of IObject with their name as how reflection work.
		*/
		class VAS_DECLSPEC IObjectFactory
		{
		public:
			IObjectFactory();
			~IObjectFactory();

			/** Create and return an instance of IObject with its name.
				  @param objName Object name that need to create using reflection, the object must be a child of IObject interface.
				  @retval New instance of IObject if success, nullptr if failed.
			*/
			std::unique_ptr<IObject> createObject(const std::string& objName);
		};
		/** @} */
	}
}