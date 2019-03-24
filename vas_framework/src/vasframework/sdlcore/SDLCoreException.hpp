//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <exception>
#include "../VASConfig.hpp"

namespace vas::sdl
{
	/**
	 * @ingroup sdl_basic
	 * @{
	 */
	/**
	 * @brief The sdl function fired out some error!!.
	 * 
	 * The SDLCoreException is an exception that fired when some thing happend within the sdl functions. It hold the
	 * error message of the SDL library when the exception is caugth.
	 */
	class VAS_DECLSPEC SDLCoreException : public std::exception
	{ /** @} */
	public:
		SDLCoreException() = default;
		char const* what() const override; /**< Get the error message of the SDL library. See official docs for 
										   * SDL_GetError() for more information. */
	};
}