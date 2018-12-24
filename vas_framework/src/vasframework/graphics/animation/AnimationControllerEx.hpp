#pragma once
#include <chrono>
#include <memory>
#include <list>
#include "Animateable.hpp"
#include "AutoControllable.hpp"
#include "../../VASConfig.hpp"

namespace vas
{
	/** @addtogroup animate
		  @{
	*/
	/** @brief Advance animation controller of the animations.
		  
		  The AnimationControllerEx is a sequential animation controller that have more feature than the simple AnimationController.
	*/
	class VAS_DECLSPEC AnimationControllerEx : public AutoControllable
	{ /** @} */
	public:
		AnimationControllerEx(); /**< Create empty animation controller. */
		~AnimationControllerEx();

		void tick() override;
		void restart() override;

		const AnimateAble* currentAnim() const; /**< Get the current animation. */
		size_t currentAnimIndex() const; /**< Get current animation index. */

		/** Inset animation to the animations list.
			  @param animation Instance of animation.
		*/
		void insertAnimation(std::unique_ptr<AnimateAble> animation);
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
		/** [Read Only] Determine if the animations finished playing.\n
				- __accessors__
					-# bool isFinished() const
		*/
		bool finished{ false };
		/** [Read & Write] Determine if the animations will be looped.\n
				- __mutators__
					-# void setLoopingAnim(bool value)
				- __accessors__
					-# bool isLoopingAnim() const
		*/
		bool loopAnim{ false };
		/** [Read & Write] Animations list\n
				- __accessors__
					-# const std::list<std::unique_ptr<AnimateAble>>& getAnimationList() const
					-# std::list<std::unique_ptr<AnimateAble>>& getAnimationList()
		*/
		std::list<std::unique_ptr<AnimateAble>> animationList;
		std::list<std::unique_ptr<AnimateAble>>::iterator curAnim{ animationList.begin() };
	};
}