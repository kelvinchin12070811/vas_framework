//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include "Scene.hpp"
#include "../DrawAble.hpp"

namespace vas
{
	/**
	 * @ingroup graphics
	 * @{
	 */
	/**
	 * @brief The DrawAble object that reference to a scene.
	 * 
	 * The Scene Reference Wraper is an object that will reference to a scene and tick and render it when the user tell
	 * it.
	 */
	class VAS_DECLSPEC SceneRefWrap : public DrawAble
	{ /** @} */
	public:
		/**
		 * Create new reference to a scene.
		 * @param[in] scene Scene instance to reference.
		 * @param[in] tickable Determine if the object will tick the scene.
		 * @param[in] drawable Determine if the object will draw the scene.
		 */
		SceneRefWrap(std::shared_ptr<Scene> scene, bool tickable = false, bool drawable = true);

		void tick() override;
		void draw(sdl::Renderer* renderer = nullptr, Camera* camera = nullptr) override;
	private:
		std::shared_ptr<Scene> scene;
		bool tickable{ false };
		bool drawable{ false };
	};
}