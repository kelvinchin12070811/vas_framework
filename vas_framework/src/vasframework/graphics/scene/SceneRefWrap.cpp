//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "SceneRefWrap.hpp"

namespace vas
{
	SceneRefWrap::SceneRefWrap(std::shared_ptr<Scene> scene, bool tickable, bool drawable) :
		scene(std::move(scene)), tickable(tickable), drawable(drawable)
	{
	}

	void SceneRefWrap::tick()
	{
		if (tickable)
		{
			scene->tick();
		}
	}

	void SceneRefWrap::draw(sdl::Renderer * renderer, Camera * camera)
	{
		if (drawable)
		{
			scene->draw();
		}
	}
}