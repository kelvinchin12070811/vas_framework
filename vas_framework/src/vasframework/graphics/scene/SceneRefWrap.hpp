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
	class SceneRefWrap : public DrawAble
	{
	public:
		SceneRefWrap(std::shared_ptr<Scene> scene, bool tickable = true, bool drawable = false);

		void tick() override;
		void draw(sdl::Renderer* renderer = nullptr, Camera* camera = nullptr) override;
	private:
		std::shared_ptr<Scene> scene;
		bool tickable{ false };
		bool drawable{ false };
	};
}