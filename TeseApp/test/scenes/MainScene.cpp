#include <boost/lexical_cast.hpp>
#include <vasframework/util/CommonTools.hpp>
#include <vasframework/util/TextTools.hpp>
#include <vasframework/container/Property.hpp>
#include <vasframework/manager/AudioManger.hpp>
#include <vasframework/graphics/Camera.hpp>
#include <vasframework/graphics/animation/AttrKeyframeAnimation.hpp>
#include <vasframework/graphics/animation/AnimationDelay.hpp>
#include "MainScene.hpp"

using namespace std::string_literals;

namespace scene
{
	vas::sreflex::IObjectAutoRegistrar<MainScene> MainScene::_registrar{};

	MainScene::MainScene()
	{
		using namespace std;
		CallRenderAssistance;
		vas::ScreenManager::getInstance().setScreenOpacity(0);
		vas::Property test1("test1", "test"s);
		vas::Property test2("test2", 0xCC50);
		vas::Property test3(test2);
		bool comResult = test3.notEqual<int>(test2);
		vas::CommonTools::getInstance().messenger(boost::format("compare result: %s"s) % (comResult ? "true"s : "false"s));
		vas::CommonTools::getInstance().messenger("test1: " + *test1.get<std::string>());

		{
			auto testSprite2Anim = make_unique<vas::AttrKeyframeAnimation>([this](double value) {
				auto colour = testSprite2->getOverlay();
				colour.alpha = static_cast<uint8_t>(value);
				testSprite2->setOverlay(colour);
			});
			testSprite2Anim->setStartValue(0);
			testSprite2Anim->setStopValue(255.0);
			testSprite2Anim->setDuration(1s);
			animation.insertAnimation(move(testSprite2Anim));
		}
		animation.insertAnimation(std::make_unique<vas::AnimationDelay>(5s));
		{
			auto testSprite2Anim = make_unique<vas::AttrKeyframeAnimation>([this](double value) {
				auto colour = testSprite2->getOverlay();
				colour.alpha = static_cast<uint8_t>(value);
				testSprite2->setOverlay(colour);
			});
			testSprite2Anim->setStartValue(255.0);
			testSprite2Anim->setStopValue(0.0);
			testSprite2Anim->setDuration(1s);
			animation.insertAnimation(move(testSprite2Anim));
		}
		animation.insertAnimation(make_unique<vas::AnimationDelay>(5s));
		animation.setLoopingAnim(true);
	}

	MainScene::~MainScene()
	{
	}
	
	void MainScene::tick()
	{
		using namespace vas;
		if (textTest->foreground->getPosition().x >= 640 - textTest->foreground->getWidth())
			movement.x = -1.0f;
		else if (textTest->foreground->getPosition().x <= 0)
			movement.x = 1.0f;

		if (textTest->foreground->getPosition().y >= 480 - textTest->foreground->getHeight())
			movement.y = -1.0f;
		else if (textTest->foreground->getPosition().y <= 0)
			movement.y = 1.0f;

		if (vas::InputManager::getInstance().isKeyTriggered(vas::sdl::Scancode::up))
			tilePos.y += -1;
		else if (vas::InputManager::getInstance().isKeyTriggered(sdl::Scancode::down))
			tilePos.y += 1;

		if (vas::InputManager::getInstance().isKeyTriggered(sdl::Scancode::left))
			tilePos.x += -1;
		else if (vas::InputManager::getInstance().isKeyTriggered(sdl::Scancode::right))
			tilePos.x += 1;

		vas::Camera::getInstance().focusOn(tilePos + vas::Vector2(16, 16));

		textTest->move(movement);
		auto& auManager = vas::AudioManger::getInstance();
		if (auManager.getME().isPlaying())
		{
			if (auManager.getBGM().isPlaying())
				auManager.getBGM().pause();
		}
		else
		{
			if (auManager.getBGM().isPaused())
				auManager.getBGM().resume();
		}
		animation.tick();
		scene::AbstractFrameCountingScene::tick();
	}

	void MainScene::draw()
	{
		scene::AbstractFrameCountingScene::draw();
		testSheet->drawTile(13, tilePos);
	}

	void MainScene::afterSceneCall()
	{
		using namespace vas;
		using namespace std::chrono_literals;
		vas::Base::getInstance().EventBeginProcessed.connect(
			boost::bind(&MainScene::eventSlot, this, boost::placeholders::_1)
		);

		sdl::mixer::Signals::ChannelFinished.connect(boost::bind(&MainScene::meFinishedPlaying, this, boost::placeholders::_1));
		vas::ScreenManager::getInstance().Signal_FadeEnd.connect(boost::bind(&MainScene::on_fadeCompleate, this, boost::placeholders::_1));
		vas::InputManager::getInstance().KeyPressed.connect(boost::bind(&MainScene::on_keyPressed, this, boost::placeholders::_1));
		testSprite = std::make_shared<vas::Sprite>("assets/textures/639111.jpg", vas::zerovector);
		testSprite2 = std::make_shared<vas::Sprite>("assets/textures/grass_side.jpg", vas::zerovector);
		testSheet = std::make_shared<vas::SpriteSheet>("assets/textures/tilesets/sandwater.png", sdl::Point(32, 32));
		textTest = std::make_shared<vas::StyledText>("This is a test to font rendering function", "assets/fonts/caladea-regular.ttf", vas::zerovector, 24, sdl::ColourPresets::white);
		textTest->setStaticOnCamera(true);
		textTest->setBackgroundOffset(vas::Vector2(3.0f, vas::Angle(45.0 + 90.0)));

		RenderAssistance->insert(VAS_INSERT_VAR(testSprite));
		RenderAssistance->insert(VAS_INSERT_VAR(testSprite2));
		RenderAssistance->insert(VAS_INSERT_VAR(textTest));

		vas::AudioManger::getInstance().playBGM("assets/audios/bgm/聞こえていますか僕らの声が.mp3");
		vas::ScreenManager::getInstance().fadeScreen(vas::ScreenManager::FadingState::fade_in, 5s);
	}

	void MainScene::beforeTerminate()
	{
		using namespace vas::sdl;
		vas::Base::getInstance().EventBeginProcessed.disconnect(
			boost::bind(&MainScene::eventSlot, this, boost::placeholders::_1)
		);
		mixer::Signals::ChannelFinished.disconnect(boost::bind(&MainScene::meFinishedPlaying, this, boost::placeholders::_1));
		vas::ScreenManager::getInstance().Signal_FadeEnd.disconnect_all_slots();
	}

	void MainScene::eventSlot(vas::sdl::Event & ev)
	{
	}

	void MainScene::on_keyPressed(vas::sdl::Keycode key)
	{
		using namespace vas::sdl;
		switch (key)
		{
		case Keycode::backspace:
				vas::CommonTools::getInstance().messenger("test event ignoreer");
				vas::Base::getInstance().setIgnoreCloseEventOnce(true);
				break;
		case Keycode::escape:
				vas::CommonTools::getInstance().messenger("Debug, close event triggered by escape");
				//ev.pushEvent(sdl::EventType::quit);
				vas::Base::getInstance().getEvent().pushEvent(EventType::quit);
				break;
		case Keycode::m:
				vas::AudioManger::getInstance().playME(me);
				break;
		case Keycode::r:
				vas::AudioManger::getInstance().getBGM().rewind();
				break;
		case Keycode::s:
				vas::AudioManger::getInstance().stopBGM();
				break;
		case Keycode::f:
				fadeController = !fadeController;
				faderTrigerer();
				break;
		}
	}

	void MainScene::meFinishedPlaying(int channel)
	{
		if (channel == vas::AudioManger::getInstance().getME().getChannel())
			vas::CommonTools::getInstance().messenger("me finished playing");
	}

	void MainScene::faderTrigerer()
	{
		using vas::ScreenManager;
		using namespace std::chrono_literals;
		switch (fadeController)
		{
		case false:
			ScreenManager::getInstance().fadeScreen(ScreenManager::FadingState::fade_in, 5s);
			break;
		case true:
			ScreenManager::getInstance().fadeScreen(ScreenManager::FadingState::fade_out, 5s);
			break;
		}
	}

	void MainScene::on_fadeCompleate(vas::ScreenManager::FadingState compleatedState)
	{
		switch (compleatedState)
		{
		case vas::ScreenManager::FadingState::fade_in:
			vas::CommonTools::getInstance().messenger("Operation fade in compleated");
			break;
		case vas::ScreenManager::FadingState::fade_out:
			vas::CommonTools::getInstance().messenger("Operation fade out compleated");
			break;
		}
	}
}