#include <boost/lexical_cast.hpp>
#include <vasframework/util/CommonTools.hpp>
#include <vasframework/util/TextTools.hpp>
#include <vasframework/container/Property.hpp>
#include <vasframework/manager/AudioManger.hpp>
#include <vasframework/graphics/Camera.hpp>
#include <vasframework/graphics/animation/AnimationDelay.hpp>
#include <vasframework/math/Clock.hpp>
#include <iomanip>
#include "MainScene.hpp"

using namespace std::string_literals;

namespace scene
{
	vas::sreflex::ReflectAbleAutoRegistrar<MainScene> MainScene::_registrar{};

	MainScene::MainScene()
	{
		using namespace std;
		vas::ScreenManager::getInstance().setScreenOpacity(0);
		vas::Property test1{ "test1", "test"s };
		vas::Property test2{ "test2", 0xCC50 };
		vas::Property test3(test2);
		bool comResult{ test3.notEqual<int>(test2) };
		vas::Log() << boost::format{ "compare result: %s"s } % (comResult ? "true"s : "false"s);
		vas::CommonTools::getInstance().messenger("test1: " + *test1.get<std::string>());

		animation.insertAnimations({
			make_unique<vas::AttrKeyframeAnimation>(vas::AttrWrap<vas::sdl::Colour>{
				[&](vas::sdl::Colour value) { testSprite2->setOverlay(value); },
				[&]() { return testSprite2->getOverlay(); },
				vas::AttrWrap<vas::sdl::Colour>::ColourChannel::alpha
				}, 0, 255.0, 1s),
			make_unique<vas::AnimationDelay>(5s),
			make_unique<vas::AttrKeyframeAnimation>(vas::AttrWrap<vas::sdl::Colour>{
				[&](vas::sdl::Colour value) { testSprite2->setOverlay(value); },
				[&]() { return testSprite2->getOverlay(); },
				vas::AttrWrap<vas::sdl::Colour>::ColourChannel::alpha
			}, 255.0, 0.0, 1s),
			make_unique<vas::AnimationDelay>(5s)
		});
		animation.setLoopingAnim(true);

		std::tm curDate = vas::Clock::ISO8601ToTm("19710101T000000Z", vas::Clock::Timezone::local);
		std::time_t curTime = vas::Clock::tmToTime_t(curDate, vas::Clock::Timezone::local);
		
		vas::Log() << curTime;
		vas::Log() << put_time(&curDate, "%Y-%m-%d %H:%M:%S");
		vas::Log() << vas::Clock::tmToISO8601(curDate, true, vas::Clock::Timezone::local);
		vas::Log() << vas::Clock::tmToISO8601(curDate, false, vas::Clock::Timezone::local);
		vas::Log() << vas::Clock::getTimezoneOffset();
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

		auto& camera = vas::Base::getInstance().getCamera();

		camera.focusOn(vas::Vector2::lerp(camera.getPosition() + (static_cast<vas::Vector2>(camera.getSize()) / 2),
			tilePos + vas::Vector2{ 16.0f, 16.0f }, 0.1f), vas::zerovector, { 800, 800 });

		textTest->move(movement);
		auto& auManager = vas::AudioManager::getInstance();
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

		{
			auto signals = {
				vas::Base::getInstance().EventBeginProcessed.connect([this](auto _1) { this->eventSlot(_1); }),
				sdl::mixer::Signals::ChannelFinished.connect([this](auto _1) { this->meFinishedPlaying(_1); }),
				vas::ScreenManager::getInstance().FadeEnd.connect([this](auto _1) { this->on_fadeCompleate(_1); }),
				vas::InputManager::getInstance().KeyPressed.connect([this](auto _1) {this->on_keyPressed(_1); })
			};
			conmng = decltype(conmng){ std::make_move_iterator(signals.begin()), std::make_move_iterator(signals.end()) };
		}

		testSprite = this->layer.emplaceInsert<vas::Sprite>("assets/textures/639111.jpg", vas::zerovector).second();
		testSprite2 = this->layer.emplaceInsert<vas::Sprite>("assets/textures/grass_side.jpg", vas::zerovector).second();
		textTest = this->layer.emplaceInsert<vas::StyledText>("This is a test to font rendering function",
			"assets/fonts/caladea-regular.ttf", vas::zerovector, 24, sdl::ColourPresets::white).second();
		
		textTest->setStaticOnCamera(true);
		textTest->setBackgroundOffset(vas::Vector2{ 3.0f, vas::Angle{ 45.0 + 90.0 } });
		testSheet = std::make_shared<vas::SpriteSheet>("assets/textures/tilesets/sandwater.png", sdl::Point{ 32, 32 });

		vas::AudioManager::getInstance().playBGM("assets/audios/bgm/聞こえていますか僕らの声が.mp3");
		vas::ScreenManager::getInstance().fadeScreen(vas::ScreenManager::FadingState::fade_in, 5s);
	}

	void MainScene::beforeTerminate()
	{
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
				vas::Base::getInstance().getEvent().pushEvent(EventType::quit);
				break;
		case Keycode::m:
				vas::AudioManager::getInstance().playME(me);
				break;
		case Keycode::r:
				vas::AudioManager::getInstance().getBGM().rewind();
				break;
		case Keycode::s:
				vas::AudioManager::getInstance().stopBGM();
				break;
		case Keycode::f:
				fadeController = !fadeController;
				faderTrigerer();
				break;
		}
	}

	void MainScene::meFinishedPlaying(int channel)
	{
		if (channel == vas::AudioManager::getInstance().getME().getChannel())
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