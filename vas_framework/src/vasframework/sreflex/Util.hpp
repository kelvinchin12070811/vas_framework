//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <string>
#include <boost/type_index.hpp>
#include "../VASConfig.hpp"

/**
 * @ingroup sreflex
 * @{
 */

/**
 * Turn a block of code into string
 * @param code Code that need to translate.
 * @return "code" in std::string
 * 
 * Defined in: vasframework/sreflex/Util.hpp
 */
#define SREFLEX_CODE2STR(code) std::string{ #code }
/** @} */

namespace vas
{
	namespace sreflex
	{
		/**
		 * @ingroup sreflex
		 * @{
		 */
		
		/**
		 * Simplifly the object name that generated by boost::typeindex from other compiler as same as msvc
		 * @param[in] input String that need to simplify
		 * 
		 * Defined in: vasframework/sreflex/Util.hpp
		 */
		VAS_DECLSPEC void simpliflyObjectName(std::string& input);
		/**
		 * Simplifly the object name that generated by boost::typeindex from other compiler as same as msvc, thsi
		 * @param[in] input Input string
		 * @return Simplified string of "input"
		 * 
		 * Defined in: vasframework/sreflex/Util.hpp
		 */
		VAS_DECLSPEC std::string simpliflyObjectNameCpy(const std::string& input);

		/**
		 * Return object's name
		 * @tparam Type Any object type
		 * @return Name of the object "Type"
		 * 
		 * Defined in: vasframework/sreflex/Util.hpp
		 */
		template <typename Type>
		std::string getObjectName()
		{
			auto result = boost::typeindex::type_id<Type>().pretty_name();
			simpliflyObjectName(result);
			return result;
		}
		
		/**
		 * Return object's name with CVR(Const, Volatile & reference)
		 * @tparam Type Any object type
		 * @return Name of the object "Type"
		 * 
		 * Defined in: vasframework/sreflex/Util.hpp
		 */
		template <typename Type>
		std::string getObjectNameWithCvr()
		{
			auto result = boost::typeindex::type_id_with_cvr<Type>().pretty_name();
			simpliflyObjectName(result);
			return result;
		}

		/**
		 * Return object's name at runtime. This function work with polymorphysm.
		 * @param[in] t Any object
		 * @return Name of the object "Type" with polymorphysm.
		 * 
		 * Defined in: vasframework/sreflex/Util.hpp
		 */
		template <typename Type>
		std::string getObjectNameRuntime(const Type& t)
		{
			auto result = boost::typeindex::type_id_runtime(t).pretty_name();
			simpliflyObjectName(result);
			return result;
		}

		/**
		 * Return the object info of an object
		 * @tparam Type Any object decalration
		 * @retval boost::typeindex::type_index of the object
		 * 
		 * Defined in: vasframework/sreflex/Util.hpp
		 */
		template <typename Type>
		boost::typeindex::type_index getObjectInfo()
		{
			return boost::typeindex::type_id<Type>();
		}

		/**
		 * Return the object info of an object with CVR(Const, Volatile & reference)
		 * @tparam Type Any object decalration
		 * @retval boost::typeindex::type_index of the object
		 * 
		 * Defined in: vasframework/sreflex/Util.hpp
		 */
		template <typename Type>
		boost::typeindex::type_index getObjectInfo_with_cvr()
		{
			return boost::typeindex::type_id_with_cvr<Type>();
		}

		/**
		 * Return the object info of an object on runtime
		 * @param[in] obj Any object
		 * @retval boost::typeindex::type_index of the object
		 * 
		 * Defined in: vasframework/sreflex/Util.hpp
		 */
		template <typename Type>
		boost::typeindex::type_index getObjectInfo_runtime(const Type& obj)
		{
			return boost::typeindex::type_id_runtime(obj);
		}
	}
}

/** @} */