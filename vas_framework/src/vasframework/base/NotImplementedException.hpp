#pragma once
#include <stdexcept>
#include "../VASConfig.hpp"

namespace vas
{
	/** @addtogroup vas_framework
		  @{
	*/
	/** @brief The exception thrown when an not implemented function called.
	*/
	class VAS_DECLSPEC NotImplementedException : public std::exception
	{ /** @} */
	public:
		NotImplementedException();
		~NotImplementedException();
		/** Get the error message. */
		const char* what() const override;
	};
}