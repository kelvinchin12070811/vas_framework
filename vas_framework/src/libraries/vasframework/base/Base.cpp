#include "Base.hpp"

namespace vas
{
	Base & Base::getInstance()
	{
		static Base instance;
		return instance;
	}

	void Base::init()
	{
		sdl::init();
		sdl::ttf::init();
		sdl::image::init();
		sdl::mixer::init();

		sdl::mixer::openAudio();
	}

	void Base::startGameLoop()
	{
		sdl::Event ev;
		while (exec.is(on))
		{
			while (ev.pollEvent())
			{
				switch (ev)
				{
				case sdl::EventType::quit:
					break;
				}
				if (exec.is(off)) break;
			}
			if (exec.is(off)) break;

			tick();
			draw();
		}
	}

	void Base::clean()
	{
		sdl::mixer::quit();
		sdl::ttf::quit();
		sdl::image::quit();
		sdl::quit();
	}

	Base::Base()
	{
	}

	Base::~Base()
	{
	}

	void Base::tick()
	{
	}

	void Base::draw()
	{
	}
}