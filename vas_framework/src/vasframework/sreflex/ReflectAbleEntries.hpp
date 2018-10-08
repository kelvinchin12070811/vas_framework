#pragma once
#include <map>
#include <memory>
#include "ReflectAble.hpp"
#include "Util.hpp"

namespace vas
{
	namespace sreflex
	{
		/** @addtogroup sreflex
			 @{
		*/

		/** Creator function of children of ReflectAble

			 Defined in: vasframework/sreflex/ReflectAbleEntries.hpp
		*/
		using ReflectAbleCreateFunction = std::unique_ptr<ReflectAble> (*)();

		/** Default creator function of ReflectAble's children
			 
			 @tparam ReflectAbleType Object that need to be created. It must be a child of ReflectAble.

			 Defined in: vasframework/sreflex/ReflectAbleEntries.hpp
		*/
		template <typename ReflectAbleType>
		std::unique_ptr<ReflectAble> createObjectBase()
		{
			return std::make_unique<ReflectAbleType>();
		}

		/** @brief Registry class that maps ReflectAble's children name to their creator function.

			  This is the singletone class that store key-value pair of ReflectAble children with its' creator function.
		*/
		class VAS_DECLSPEC ReflectAbleEntries
		{
		public:
			using ObjectMap = std::map<std::string, ReflectAbleCreateFunction>;/**< Registry that store key to value mapping
																		   to the ReflectAble children and its creator function*/

			/** Return the singletone instance of ReflectAbleEntries
			*/
			static ReflectAbleEntries& getInstance();

			std::unique_ptr<ObjectMap>& getRegistry();

			/** Register an instance of ReflectAble child*/
			bool registerInstance(const std::string& objName, ReflectAbleCreateFunction creator);
		private:
			ReflectAbleEntries();
			~ReflectAbleEntries();

			std::unique_ptr<ObjectMap> registry{ nullptr }; /**< [Read Only] Registry that store data
																about all instance of ReflectAble
																- __accessors__
																	-# std::unique_ptr<ObjectMap>& getRegistry()
															*/
		};

		/** @} */
	}
}