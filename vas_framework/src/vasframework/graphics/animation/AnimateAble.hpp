#pragma once

namespace vas
{
	/** @addtogroup animate
		  @{
	*/
	/** @brief The interface of all animations.
		  
		  The parent of all animations that use with this library.
	*/
	class AnimateAble
	{ /** @} */
	public:
		virtual void tick() = 0 {} /**< Tick or update the animation. */
		virtual bool done() const = 0 {} /**< Deternime if the animation is finished. */
		virtual ~AnimateAble() = 0 {}
	};
}