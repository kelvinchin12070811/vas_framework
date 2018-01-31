#include "Base.hpp"
#include "../manager/SceneManager.hpp"

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
		sdl::mixer::closeAudio();
		sdl::mixer::quit();
		sdl::ttf::quit();
		sdl::image::quit();
		sdl::quit();
	}

	void Base::setWindow(const sdl::Window & instance)
	{
		mainWindow = instance;
	}

	void Base::setWindow(sdl::Window && instance)
	{
		mainWindow = std::move(instance);
	}

	void Base::setRenderer(const sdl::Renderer & instance)
	{
		mainRenderer = instance;
	}

	void Base::setRenderer(sdl::Renderer && instance)
	{
		mainRenderer = std::move(instance);
	}

	Base::Base()
	{
	}

	Base::~Base()
	{
	}

	void Base::tick()
	{
		if (!SceneManager::getInstance().isEmpty())
		{
			SceneManager::getInstance().current()->tick();
		}
	}

	void Base::draw()
	{
		if (!SceneManager::getInstance().isEmpty)
		{
			if (doubleSceneRendering.is(on) && SceneManager::getInstance().atleast2Scene())
				SceneManager::getInstance().previous()->draw();
			SceneManager::getInstance().current()->draw();
		}
	}
}