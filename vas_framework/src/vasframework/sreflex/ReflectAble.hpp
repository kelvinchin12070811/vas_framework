#pragma once
#include "../VASConfig.hpp"

/*
	Interface for sreflex libary's instance
*/
namespace vas
{
	namespace sreflex
	{
		/** @addtogroup sreflex
		@{ */
		/*! \brief The interface that all reflectable object need to inherit.

			 ReflectAble is the interface that all object that need to support reflection to inherit.
		*/
		class ReflectAble
		{
		public:
			ReflectAble() {}
			virtual ~ReflectAble() = 0 {}
		};
		/*! @} */
	}
}