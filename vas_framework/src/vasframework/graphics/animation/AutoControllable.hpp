//======================================================================
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
	 * @brief Interface of all animation controller.
	 * 
	 * The abstract interface of all animation controllers that will operate automatically.
	 */
	class AutoControllable
	{ /** @} */
	public:
		virtual void tick() = 0 {} /**< Tick or update the controller. */
		virtual void restart() = 0 {} /**< Restart the controller. */
		virtual ~AutoControllable() = 0;
	};

	inline AutoControllable::~AutoControllable() = default;
}