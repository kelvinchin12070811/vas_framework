#pragma once
#include <exception>
#include <string>

namespace vas
{
	/** @addtogroup vas_framework
		  @{
	*/
	/** @brief Scene call failed.
		  
		  This exception throw by vas::SceneManager if a Scene call is failed.
	*/
	class SceneCallFailed : std::exception
	{ /** @} */
	public:
		SceneCallFailed();
		explicit SceneCallFailed(const std::string& sceneName);
		~SceneCallFailed();

		/** Get the discription of this exception. */
		const char* what() const override;
	private:
		std::string sceneName;
	};
}