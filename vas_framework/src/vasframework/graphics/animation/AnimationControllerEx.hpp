//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <chrono>
#include <memory>
#include <list>
#include "Animateable.hpp"
#include "AutoControllable.hpp"
#include "../../VASConfig.hpp"

namespace vas
{
	/**
	 * @ingroup animate
	 * @{
	 */
	/**
	 * @brief Advance animation controller of the animations.
	 * 
	 * The AnimationControllerEx is a sequential animation controller that have more feature than the simple AnimationController.
	 */
	class VAS_DECLSPEC AnimationControllerEx : public AutoControllable
	{ /** @} */
	public:
		AnimationControllerEx() = default; /**< Create empty controller. */
		void tick() override;
		void restart() override;

		const AnimateAble* currentAnim() const; /**< Get the current animation. */
		size_t currentAnimIndex() const; /**< Get current animation index. */

		/**
		 * Inset animation to the animations list.
		 * @param[in] animation Instance of animation.
		 */
		void insertAnimation(std::unique_ptr<AnimateAble> animation);
		/**
		 * Insert animations with initializer_list
		 * @param[in] animations Instances of animations in initializer list.
		 */
		void insertAnimations(std::initializer_list<std::unique_ptr<AnimateAble>> animations);
		/** Remove animation at the back. */
		void removeAnimation();
		/** Clear all animation. */
		void clear();

		bool isEmpty() const; /**< Determine if the animations list is empty. */
		size_t size() const; /**< Get the size of the animations list. */

	public: //accessors
		bool isFinished() const;
		bool isLoopingAnim() const;
		std::list<std::unique_ptr<AnimateAble>>& getAnimationList();
		const std::list<std::unique_ptr<AnimateAble>>& getAnimationList() const;

	public: //mutators
		void setLoopingAnim(bool value);

	private:
		/**
		 * Determine if the animations finished playing.
		 * ####Accessors
		 * -# bool isFinished() const
		 */
		bool finished{ false };
		/**
		 * Determine if the animations will be looped.
		 * ####Mutators
		 * -# void setLoopingAnim(bool value)
		 *
		 * ####Accessors
		 * -# bool isLoopingAnim() const
		 */
		bool loopAnim{ false };
		/**
		 * Animations list
		 * ####Accessors
		 * -# const std::list<std::unique_ptr<AnimateAble>>& getAnimationList() const
		 * -# std::list<std::unique_ptr<AnimateAble>>& getAnimationList()
		 */
		std::list<std::unique_ptr<AnimateAble>> animationList;
		std::list<std::unique_ptr<AnimateAble>>::iterator curAnim{ animationList.begin() };
	};
}