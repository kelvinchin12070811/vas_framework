#pragma once

namespace vas
{
	/** @addtogroup animate
		  @{
	*/
	/** @brief Interface of all animation controller.
		  
		  The abstract interface of all animation controllers that will operate automatically.
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