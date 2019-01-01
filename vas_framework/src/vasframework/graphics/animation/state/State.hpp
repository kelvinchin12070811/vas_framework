//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <memory>
#include "../AnimateAble.hpp"

namespace vas
{
	/** @addtogroup animate
		  @{
	*/
	/** @brief A structure that contain the animation of the state */
	struct State
	{ /** @} */
		std::unique_ptr<AnimateAble> animation;
	};
}