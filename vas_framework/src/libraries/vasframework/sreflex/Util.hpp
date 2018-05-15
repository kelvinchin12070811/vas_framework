#pragma once
#include <string>
#include <boost/type_index.hpp>
#include "../VASConfig.hpp"

#define SREFLEX_CODE2STR(code) std::string(#code)

namespace vas
{
	namespace sreflex
	{
		template <typename Type>
		std::string getObjectName()
		{
			auto result = boost::typeindex::type_id<Type>().pretty_name();
			simpliflyObjectName(result);
			return result;
		}

		template <typename Type>
		std::string getObjectNameWithCvr()
		{
			auto result = boost::typeindex::type_id_with_cvr<Type>().pretty_name();
			simpliflyObjectName(result);
			return result;
		}

		template <typename Type>
		std::string getObjectNameRuntime(const Type& t)
		{
			auto result = boost::typeindex::type_id_runtime(t).pretty_name();
			simpliflyObjectName(result);
			return result;
		}

		template <typename Type>
		boost::typeindex::type_index getObjectInfo()
		{
			return boost::typeindex::type_id<Type>()
		}

		template <typename Type>
		boost::typeindex::type_index getObjectInfo_with_cvr()
		{
			return boost::typeindex::type_id_with_cvr<Type>()
		}

		template <typename Type>
		boost::typeindex::type_index getObjectInfo_runtime()
		{
			return boost::typeindex::type_id_runtime<Type>()
		}

		VAS_DECLSPEC void simpliflyObjectName(std::string& input);
		VAS_DECLSPEC std::string simpliflyObjectNameCpy(const std::string& input);
	}
}