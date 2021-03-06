//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <list>
#include <memory>
#include <tuple>
#include "AnimateAble.hpp"
#include "../sprites/SpriteSheet.hpp"
#include "../../math/Clock.hpp"
#include "../../VASConfig.hpp"
namespace vas
{
	/** @ingroup animate
		  @{
	*/
	/** @brief Advance sequential frame animation.
		  
		  The StripAnimation is a frame based animation. StripAnimation also work with mulitple spritesheets.
	*/
	class VAS_DECLSPEC StripAnimation : public AnimateAble, public std::list<std::tuple<size_t, SpriteSheet*, Clock::DurationType>>
	{ /** @} */
	public:
		StripAnimation() = default; /**< Create animation. */

		/**
		 * Insert frame to back.
		 * @param[in] frame Index of frame on spritesheet.
		 * @param[in] spritesheet Spritesheet that  contain the @p frame, nullptr to use previous spritesheet.
		 * @param[in] stayTime Duration of the frame stayed, zero (Clock::DurationType()) to use previous stayTime.
		 */
		void insertFrame(size_t frame, SpriteSheet* spritesheet = nullptr, Clock::DurationType stayTime = Clock::DurationType());

		void tick() override;

		/**
		 * Get current frame shown.
		 * @return Pair of index of frame on the returned SpriteSheet.
		 */
		std::pair<size_t, const SpriteSheet*> getCurrentFrame() const;
	private:
		iterator currentFrame;
		std::unique_ptr<Clock> updateClock;
	};
}