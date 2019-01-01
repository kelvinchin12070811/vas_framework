//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
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