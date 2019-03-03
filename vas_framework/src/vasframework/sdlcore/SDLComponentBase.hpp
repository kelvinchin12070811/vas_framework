//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <memory>
#include <functional>

namespace vas::sdl
{
	/** @addtogroup sdl_basic
		  @{
	*/
	/** @brief Empty component instance.
		  
		  Represent as an empty component instance. The operator used is vas::sdl::nullcomponent.
	*/
	const class NullComponent_t
	{
	public:
		operator std::nullptr_t() const
		{
			return nullptr;
		}
	} nullcomponent = {};
	/** @} */
}