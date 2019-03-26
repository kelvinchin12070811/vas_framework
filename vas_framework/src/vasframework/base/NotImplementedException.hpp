//===========================================================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//===========================================================================================================
#pragma once
#include <stdexcept>
#include "../VASConfig.hpp"

namespace vas
{
	/**
	 * @ingroup vas_framework
	 * @{
	 */
	/**
	 * @brief The exception thrown when an not implemented function called.
	 */
	class VAS_DECLSPEC NotImplementedException : public std::exception
	{ /** @} */
	public:
		NotImplementedException() = default;
		/** Get the error message. */
		const char* what() const override;
	};
}