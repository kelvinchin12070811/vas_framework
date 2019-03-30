//===========================================================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//===========================================================================================================
#include "BasicTexturedWindow.hpp"
#include "../../base/Base.hpp"
#include "WindowBase.hpp"

namespace vas::imgui
{
	BasicTexturedWindow::BasicTexturedWindow(const std::string & spriteId, sdl::Point offset):
		offset(std::move(offset))
	{
		background = std::make_unique<Sprite>(spriteId, zerovector);
	}

	void BasicTexturedWindow::tick()
	{
		background->tick();
	}

	void BasicTexturedWindow::draw(sdl::Renderer * renderer, Camera * camera)
	{
		background->draw();
	}

	void BasicTexturedWindow::applyStyle(WindowBase * win)
	{
		WindowStyle::applyStyle(win);
		auto&& rect = win->getWinRect();
		background->move(vas::Vector2{
			static_cast<float>(rect.x + this->offset.x),
			static_cast<float>(rect.y + this->offset.y)
		});
	}
}