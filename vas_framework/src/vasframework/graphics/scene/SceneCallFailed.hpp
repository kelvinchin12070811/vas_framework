//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <exception>
#include <string>

namespace vas
{
	/**
	 * @ingroup graphics
	 * @{
	 */
	/**
	 * @brief Scene call failed.
	 *
	 * This exception throw by vas::SceneManager if a Scene call is failed.
	 */
	class SceneCallFailed : std::exception
	{ /** @} */
	public:
		SceneCallFailed() = default;
		explicit SceneCallFailed(const std::string& sceneName);

		/** Get the discription of this exception. */
		const char* what() const override;
	private:
		std::string sceneName;
	};
}