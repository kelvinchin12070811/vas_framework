//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <functional>

namespace vas
{
	/**
	 * @ingroup animate
	 * @{
	 */
	/**
	 * @brief The wraper of the numeric attribute of object.
	 */
	template <typename AttrType>
	struct AttrWrap
	{ /** @} */
		using WrappedType = AttrType;
		/**
		 * Create wrapper of setter
		 * @param[in] mutator Function pointer to the setter of object.
		 */
		AttrWrap(std::function<void(AttrType)> mutator) : mutator(mutator) {}
		/** Access the setter. */
		void operator()(double value)
		{
			mutator(static_cast<AttrType>(value));
		}
	protected:
		std::function<void(AttrType)> mutator;
	};
}