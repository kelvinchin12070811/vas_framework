#include "MainScene.hpp"
#include "../../libraries/vasframework/util/CommonTools.hpp"
#include "../../libraries/vasframework/util/TextTools.hpp"
#include "../../libraries/vasframework/container/Property.hpp"
#include "../../libraries/vasframework/manager/AudioManger.hpp"

using namespace std::string_literals;

namespace scene
{
	vas::sreflex::IObjectAutoRegistrar<MainScene> MainScene::_registrar(SREFLEX_OBJ_NAME(scene::MainScene));

	MainScene::MainScene()
	{
		CallRenderAssistance;
		vas::Property test1("test1", "test"s);
		vas::Property test2("test2", 0xCC50);
		vas::Property test3(test2);
		bool comResult = test3.notEqual<int>(test2);
		vas::CommonTools::getInstance().messengerf(boost::format("compare result: %s"s) % (comResult ? "true"s : "false"s));
		vas::CommonTools::getInstance().messenger("test1: " + *test1.get<std::string>());
	}

	MainScene::~MainScene()
	{
	}
	
	void MainScene::tick()
	{
		auto& auManager = vas::AudioManger::getInstance();
		if (auManager.ME().isPlaying())
		{
			if (auManager.BGM().isPlaying())
				auManager.BGM().pause();
		}
		else
		{
			if (auManager.BGM().isPaused())
				auManager.BGM().resume();
		}
		scene::AbstractFrameCountingScene::tick();
	}

	void MainScene::draw()
	{
		scene::AbstractFrameCountingScene::draw();
		testSheet->drawTile(13, vas::Vector2(56, 67));
	}

	void MainScene::Signal_afterSceneCall()
	{
		vas::Base::getInstance().EventProcessorSignal(vas::Base::SignalsType::EventProcessor::preEventLoop).connect(
			boost::bind(&MainScene::eventSlot, this, boost::placeholders::_1)
		);

		sdl::mixer::Signals::onChannelFinished.connect(boost::bind(&MainScene::meFinishedPlaying, this, boost::placeholders::_1));

		testSprite = std::make_shared<vas::Sprite>("assets/textures/639111.jpg", vas::Vector2());
		testSheet = std::make_shared<vas::SpriteSheet>("assets/textures/tilesets/sandwater.png", sdl::Point(32, 32));
		RenderAssistance->insert(std::make_pair("testSprite", testSprite));

		vas::AudioManger::getInstance().playBGM("assets/audios/bgm/聞こえていますか僕らの声が.mp3");
	}

	void MainScene::Signal_beforeTerminate()
	{
		vas::Base::getInstance().EventProcessorSignal(vas::Base::SignalsType::EventProcessor::preEventLoop).disconnect(
			boost::bind(&MainScene::eventSlot, this, boost::placeholders::_1)
		);
		sdl::mixer::Signals::onChannelFinished.disconnect(boost::bind(&MainScene::meFinishedPlaying, this, boost::placeholders::_1));
	}

	void MainScene::eventSlot(sdl::Event & ev)
	{
		switch (ev)
		{
		case sdl::EventType::keydown:
			eventKeyPressHwnd(ev, true);
			break;
		}
	}

	void MainScene::eventKeyPressHwnd(sdl::Event&ev, bool isKeyDown)
	{
		if (isKeyDown)
		{
			if (vas::InputManager::getInstance().isKeyTriggeredEv(sdl::Keycode::backspace))
			{
				vas::CommonTools::getInstance().messenger("test event ignoreer");
				vas::Base::getInstance().IgnoreCloseEventOnce() = true;
			}
			else if (vas::InputManager::getInstance().isKeyTriggeredEv(sdl::Keycode::escape))
			{
				vas::CommonTools::getInstance().messenger("Debug, close event triggered by escape");
				ev.pushEvent(sdl::EventType::quit);
			}
			else if (vas::InputManager::getInstance().isKeyTriggeredEv(sdl::Keycode::m))
			{
				vas::AudioManger::getInstance().playME(me);
			}
			else if (vas::InputManager::getInstance().isKeyTriggeredEv(sdl::Keycode::r))
			{
				vas::AudioManger::getInstance().BGM().rewind();
			}
			else if (vas::InputManager::getInstance().isKeyTriggeredEv(sdl::Keycode::s))
				vas::AudioManger::getInstance().stopBGM();
		}
	}

	void MainScene::meFinishedPlaying(int channel)
	{
		if (channel == vas::AudioManger::getInstance().ME().getChannel())
			vas::CommonTools::getInstance().messenger("me finished playing");
	}
}