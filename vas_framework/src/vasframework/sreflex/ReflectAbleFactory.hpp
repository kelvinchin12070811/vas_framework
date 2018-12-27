#pragma once
#include <memory>
#include "ReflectAbleEntries.hpp"

namespace vas
{
	namespace sreflex
	{
		/** @addtogroup sreflex
			  @{
		*/
		/** @brief The factory class that create ReflectAble instance with their name

			  ReflectAbleFactory class create and return the instance of ReflectAble with their name as how reflection work.
		*/
		class VAS_DECLSPEC ReflectAbleFactory
		{
		public:
			ReflectAbleFactory() = default;
			/** Create and return an instance of ReflectAble with its name.
				  @param objName Object name that need to create using reflection, the object must be a child of ReflectAble interface.
				  @retval New instance of ReflectAble if success, nullptr if failed.
			*/
			std::unique_ptr<ReflectAble> createObject(const std::string& objName);
		};
		/** @} */
	}
}