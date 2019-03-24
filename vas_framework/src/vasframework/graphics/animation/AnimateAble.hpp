//=====================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once

namespace vas
{
	/**
	 * @ingroup animate
	 * @{
	 */
	/**
	 * @brief The interface of all animations.
	 * 
	 * The parent of all animations that use with this library.
	 */
	class AnimateAble
	{ /** @} */
	public:
		virtual void tick() = 0 {} /**< Tick or update the animation. */
		virtual bool done() const final; /**< Deternime if the animation is finished. */
		virtual void reset(); /**< Reset the animations. */
		virtual ~AnimateAble() = 0;
	protected:
		bool finished{ false };
	};
}