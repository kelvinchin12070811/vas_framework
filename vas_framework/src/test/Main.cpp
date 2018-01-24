#include "../libraries/vasframework/sdlcore/SDLCore.hpp"
#include <exception>
#include <SDL_image.h>
#include <Windows.h>

int main(int argc, char** argv)
{
	try
	{
		sdl::init();
		sdl::image::init();
		sdl::mixer::init();
		sdl::mixer::openAudio(sdl::mixer::DefaultValues::frequency, sdl::mixer::DefaultValues::format, sdl::mixer::DefaultValues::channelCount, sdl::mixer::DefaultValues::chunkSize);
		sdl::Window mainWindow("hello world", sdl::Point(640, 480), sdl::Window::Flags::shown);
		if (mainWindow == nullptr)
			throw sdl::SDLCoreException();

		sdl::Renderer mainRenderer(mainWindow, sdl::Renderer::defIndex, sdl::Renderer::RendererFlags::accelerated);
		if (mainRenderer == nullptr)
			throw sdl::SDLCoreException();

		mainWindow.show();

		/*sdl::Surface tempSurface;
		tempSurface.loadImage(u8"assets/textures/639111.jpg");
		if (tempSurface == nullptr) throw std::runtime_error(sdl::getError());*/

		sdl::Texture testTexture;// (mainRenderer, tempSurface);
		testTexture.loadImage(mainRenderer, u8"assets/textures/639111.jpg");
		if (testTexture == nullptr) throw sdl::SDLCoreException();

		sdl::Rect testRect;
		testTexture.queryTexture(&testRect.w, &testRect.h);

		sdl::mixer::Music bgm(u8"assets/audios/bgm/聞こえていますか僕らの声が.mp3");
		sdl::mixer::Chunk me(u8"assets/audios/me/rain1.ogg");
		if (bgm == nullptr) throw sdl::SDLCoreException();
		if (me == nullptr) throw sdl::SDLCoreException();
		bgm.play();


		bool exec = true;
		sdl::Event ev;
		while (exec)
		{
			while (ev.pollEvent())
			{
				switch (ev)
				{
				case sdl::EventType::quit:
					exec = false;
					break;
				case sdl::EventType::keydown:
					if (ev.key().keysym.sym == SDLK_ESCAPE)
						ev.pushEvent(sdl::EventType::quit);
					else if (ev.key().keysym.sym == SDLK_r)
						bgm.rewind();
					else if (ev.key().keysym.sym == SDLK_m)
						me.play(0);
					break;
				}
				if (exec == false) break;
			}
			if (exec == false) break;

			if (me.isPlaying(0))
			{
				if (bgm.isPlaying())
					bgm.pause();
			}
			else
			{
				if (bgm.isPaused())
					bgm.resume();
			}

			mainRenderer.clear();
			mainRenderer.copy(testTexture, &testRect, &testRect);
			mainRenderer.present();
		}

		sdl::mixer::closeAudio();
		bgm = nullptr;
		mainWindow = nullptr;
		mainRenderer = nullptr;
		sdl::quit();
		sdl::image::quit();
		sdl::mixer::quit();
	}
	catch (const std::exception& e)
	{
		MessageBeep(MB_ICONERROR);
		MessageBoxA(nullptr, e.what(), u8"Unhandled Exception Occur", MB_ICONERROR);
		return -1;
	}

	return 0;
}