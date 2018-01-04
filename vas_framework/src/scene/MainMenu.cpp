#include "MainMenu.hpp"
#include "../libraries/VASFramework/manager/InputManager.hpp"
#include "../libraries/VASFramework/manager/AudioManager.hpp"
#include "../libraries/VASFramework/base/Camera.hpp"

namespace scene
{
	const sreflex::IObjectAutoRegister<scene::MainMenu> MainMenu::__auto_register(SREFLEX_VAR_NAME(scene::MainMenu));

	MainMenu::MainMenu()
	{
		VAS_CONNECT_PRE_EVENT(&MainMenu::eventSlot);
		CallRenderAssistance;
		vas::FadingManager::getInstance().fadeOutScreen();
		vas::CommonTools::getInstance().messenger(L"场景: " + VAS_TEXTTOOLS_GETVARNAME(scene::MainMenu) + L"已被加载");
		someSprite = std::make_shared<vas::SpriteSheet>(L"assets/textures/grass_side.png", vas::Vector2(30.0f, 20.0f), 32, 32);
		someSprite->setCenter(SDL_Point{ someSprite->getWidth() / 2, someSprite->getHeight() / 2 });
		someSprite->setColour(vas::Colour(255, 255, 255, 50));

		background = std::make_shared<vas::Sprite>(L"assets/textures/639098.jpg", vas::Vector2(0, 0));
		someText = std::make_shared<vas::Text>(L"VAS Framework " + vas::Base::frameworkVersion(), vas::Vector2(0, 0), L"assets/fonts/caladea-regular.ttf", 25, vas::ColourPresets::white);
		someText->setStaticOnCamera(true);
		RenderAssistance->insert(VAS_ITEM_VAR(background));
		RenderAssistance->insert(VAS_ITEM_VAR(someSprite));

		RenderAssistance->insert(VAS_ITEM_VAR(someText));
		RenderAssistance->moveDown(VAS_TEXTTOOLS_GETVARNAME(someSprite), UINT_MAX);
		vas::CommonTools::getInstance().messenger(std::to_wstring(someSprite->getCount()));
	}


	MainMenu::~MainMenu()
	{
		VAS_DISCONNECT_PRE_EVENT(&MainMenu::eventSlot);
	}

	void MainMenu::tick()
	{
		const auto cameraInstance = &vas::Camera::getInstance;
		const auto getCameraPosition = std::bind(&vas::Camera::getPosition, &cameraInstance());
		//vas::Colour spriteColour = vas::ColourPresets::white;
		//if (someSprite->getColour() != spriteColour)
		//	someSprite->setColour(spriteColour);

		if (vas::InputManager::getInstance().keyTriggeredLive(SDL_SCANCODE_LSHIFT))
			dash = true;
		else
			dash = false;

		float moveSpeed = dash ? 2.0f : 1.0f;
		if (vas::InputManager::getInstance().keyTriggeredLive(SDL_SCANCODE_LEFT))
			someSprite->move(vas::Vector2(-1 * moveSpeed, 0));
		else if (vas::InputManager::getInstance().keyTriggeredLive(SDL_SCANCODE_RIGHT))
			someSprite->move(vas::Vector2(1 * moveSpeed, 0));
		else if (vas::InputManager::getInstance().keyTriggeredLive(SDL_SCANCODE_UP))
			someSprite->move(vas::Vector2(0, -1 * moveSpeed));
		else if (vas::InputManager::getInstance().keyTriggeredLive(SDL_SCANCODE_DOWN))
			someSprite->move(vas::Vector2(0, 1 * moveSpeed));

		someSprite->setRotation(someSprite->getRotation() + vas::Angle(1.0));

		SceneBase::tick();
		vas::Vector2 targetDestination = someSprite->getPosition() + vas::Vector2(someSprite->getWidth() / 2.0f, someSprite->getHeight() / 2.0f);
		vas::Camera::getInstance().targetOn(vas::Vector2::lerp(getCameraPosition(), targetDestination, 0.1f));
	}

	void MainMenu::draw()
	{
		SceneBase::draw();
	}

	void MainMenu::eventSlot(SDL_Event& eventBus)
	{
		switch (eventBus.type)
		{
		case SDL_EventType::SDL_KEYDOWN:
			if (vas::InputManager::getInstance().keyTriggered(SDL_SCANCODE_SPACE))
				vas::Camera::getInstance().zoom(2);
			else if (vas::InputManager::getInstance().keyTriggered(SDL_SCANCODE_RSHIFT))
				vas::Camera::getInstance().zoom(0.5f);
			else if (vas::InputManager::getInstance().keyTriggered(SDL_SCANCODE_ESCAPE))
				vas::Base::getInstance().postEvent(SDL_EventType::SDL_QUIT);
			else if (vas::InputManager::getInstance().keyTriggered(SDL_SCANCODE_P))
				vas::AudioManager::getInstance().playMe(L"assets/audios/me/Town5.ogg", 1, 5);
			break;
		}
	}

	void MainMenu::Signal_afterSceneCall()
	{
		vas::FadingManager::getInstance().fadeInScreen(5);
		//vas::AudioManager::getInstance().playBgm(L"assets/audios/bgm/聞こえていますか僕らの声が.mp3", 5);
	}
}