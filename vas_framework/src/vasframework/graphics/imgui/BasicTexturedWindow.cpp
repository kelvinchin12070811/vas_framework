#include "BasicTexturedWindow.hpp"
#include "../../base/Base.hpp"

namespace vas::imgui
{
	BasicTexturedWindow::BasicTexturedWindow(const std::string & spriteId, sdl::Point offset):
		offset(std::move(offset))
	{
		vas::Vector2 position{
			static_cast<float>(this->winRect->x + this->offset.x),
			static_cast<float>(this->winRect->y + this->offset.y)
		};
		background = std::make_unique<Sprite>(spriteId, position);
	}

	void BasicTexturedWindow::tick()
	{
		background->tick();
	}

	void BasicTexturedWindow::draw(sdl::Renderer * renderer, Camera * camera)
	{
		background->draw();
	}
}