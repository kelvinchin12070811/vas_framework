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
		virtual bool done() const final; /**< Deternime if the animation is finished. */
		virtual void reset(); /**< Reset the animations. */
		virtual ~AnimateAble() = 0 {}
	protected:
		bool finished{ false };
	};
}