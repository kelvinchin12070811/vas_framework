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