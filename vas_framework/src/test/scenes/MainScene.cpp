#include <Windows.h>
#include "MainScene.hpp"
#include "../../libraries/vasframework/util/TextTools.hpp"
#include "../../libraries/vasframework/container/Property.hpp"
#include "../../libraries/vasframework/manager/TextureManager.hpp"

using namespace std::string_literals;

namespace scene
{
	vas::sreflex::IObjectAutoRegistrar<MainScene> MainScene::_registrar(SREFLEX_OBJ_NAME(scene::MainScene));

	MainScene::MainScene()
	{
		vas::Property test1 = "test"s;
		vas::Property test2 = "test"s;
		vas::Property test3(test2);
		bool comResult = test3.notEqual<std::string>(test2);
		vas::TextTools::println("compare result: "s + (comResult ? "true" : "false"));
		vas::TextTools::println("test1: " + *test1.get<std::string>());
	}

	MainScene::~MainScene()
	{
	}
	
	void MainScene::tick()
	{
		if (me.isPlaying())
		{
			if (bgm.isPlaying())
				bgm.pause();
		}
		else
		{
			if (bgm.isPaused())
				bgm.resume();
		}

		angle += 0.6;
		if (angle >= 360.0)
			angle -= 360.0;

		//vas::TextTools::printfln(boost::format("Last fps: %d") % vas::Base::getInstance().getLastFpsCount());
		SetConsoleTitle(vas::TextTools::stows((boost::format("Last fps: %d") % vas::Base::getInstance().getLastFpsCount()).str()).c_str());
	}

	void MainScene::draw()
	{
		auto renderer = vas::Base::getInstance().Renderer();
		renderer.copyEx(testTexture, &testRect, &testRect, angle, center);
	}

	void MainScene::Signal_afterSceneCall()
	{
		{
			auto& signal = vas::Base::getInstance().EventProcessorSignal(vas::Base::SignalsType::EventProcessor::preEventLoop);
			signal.connect(boost::bind(&MainScene::eventSlot, this, boost::placeholders::_1));
		}

		bgm.load("assets/audios/bgm/聞こえていますか僕らの声が.mp3");
		me.load("assets/audios/me/rain1.ogg");

		if (vas::TextureManager::getInstance().has("assets/textures/639111.jpg"))
		{
			testTexture = vas::TextureManager::getInstance().get("assets/textures/639111.jpg");
		}
		else
		{
			testTexture.loadImage(vas::Base::getInstance().Renderer(), "assets/textures/639111.jpg");
			vas::TextureManager::getInstance().insert("assets/textures/639111.jpg", testTexture);
		}
		
		if (bgm == sdl::emptycomponent ||
			me == sdl::emptycomponent ||
			testTexture == sdl::emptycomponent)
		{
			throw sdl::SDLCoreException();
		}

		testTexture.queryTexture(&testRect.w, &testRect.h);
		center.x = testRect.w / 2;
		center.y = testRect.h / 2;
		bgm.play();
	}

	void MainScene::Signal_beforeTerminate()
	{
		{
			auto& signal = vas::Base::getInstance().EventProcessorSignal(vas::Base::SignalsType::EventProcessor::preEventLoop);
			signal.disconnect(boost::bind(&MainScene::eventSlot, this, boost::placeholders::_1));
		}
	}

	void MainScene::eventSlot(sdl::Event & ev)
	{
		switch (ev)
		{
		case sdl::EventType::keydown:
			switch (static_cast<sdl::Keycode>(ev.key().keysym.sym))
			{
			case sdl::Keycode::backspace:
				vas::TextTools::println("Debug, test event ignoreer");
				vas::Base::getInstance().IgnoreCloseEventOnce() = true;
				break;
			case sdl::Keycode::escape:
				vas::TextTools::println("Debug, close event triggered by escape");
				ev.pushEvent(sdl::EventType::quit);
				break;
			case sdl::Keycode::m:
				me.play();
				break;
			case sdl::Keycode::r:
				bgm.rewind();
				break;
			}
			break;
		}
	}
}