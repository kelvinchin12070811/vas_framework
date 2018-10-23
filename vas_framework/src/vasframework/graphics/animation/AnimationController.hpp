#pragma once
#include <chrono>
#include "AutoControllable.hpp"
#include "../../VASConfig.hpp"
#include "../../math/Counter.hpp"
#include "AnimationStrip.hpp"

namespace vas
{
	/** @addtogroup animate
		  @{
	*/
	/** @brief The simple animation controller.
		  
		  The 2D spritesheet based sequential animation controller. Indexing the index of the frame of animation contained by
		  a spritesheets.
	*/
	class VAS_DECLSPEC AnimationController : public AutoControllable
	{ /** @} */
	public:
		/** Create empty controller. */
		AnimationController();
		/** Create animation controller with data.
			  @param frames Frames of an animation.
			  @param updateDelay Time for each frame to stay on the screen.
		*/
		AnimationController(const AnimationStrip& frames, std::chrono::milliseconds updateDelay);
		~AnimationController();

		/** Load the animation.
			  @param frames Frames of an animation.
			  @param updateDelay Time for each frame to stay on the screen.
		*/
		void load(const AnimationStrip& frames, std::chrono::milliseconds updateDelay);
		void tick() override;

		void reset();
		void restart() override;

	public: //getters
		AnimationStrip::value_type getCurrentFrame(); /**< Get current frame's index on spritesheet that display on screen. */
		size_t getCurrentFrameIndex(); /**< Get current internal frame index. */

	private:
		AnimationStrip frames;
		Counter frameIndexer;
		Counter frameUpdateTimer;
	};
}