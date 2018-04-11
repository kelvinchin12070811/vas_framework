#pragma once
#include "../VASConfig.hpp"

/*
	Interface for sreflex libary's instance

*/
namespace vas
{
	namespace sreflex
	{
		class IObject
		{
		public:
			IObject() {}
			virtual ~IObject() = 0 {}
		};
	}
}