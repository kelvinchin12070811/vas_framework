//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <vector>

namespace vas
{
	/** @addtogroup animate
		  @{
	*/
	/** The strip of animation that contain the index of the frames on the spritesheets. */
	using AnimationStrip = std::vector<size_t>;
	/** @} */
}