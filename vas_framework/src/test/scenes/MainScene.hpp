#pragma once
#include <memory>
#include "../../libraries/vasframework/sreflex/IObjectAutoRegistrar.hpp"
#include "../../libraries/vasframework/base/Base.hpp"
#include "../../libraries/vasframework/manager/InputManager.hpp"
#include "../../libraries/vasframework/graphics/sprites/SpriteSheet.hpp"
#include "../../libraries/vasframework/manager/ScreenManager.hpp"
#include "../../libraries/vasframework/graphics/text/StyledText.hpp"
#include "AbstractFrameCountingScene.hpp"

namespace scene
{
	class MainScene : public AbstractFrameCountingScene, public vas::sreflex::IObject
	{
	public:
		MainScene();
		~MainScene();

		void tick() override;
		void draw() override;

		void Signal_afterSceneCall() override;
		void Signal_beforeTerminate() override;

		void eventSlot(sdl::Event& ev);
	private:
		//void eventKeyPressHwnd(sdl::Event& ev, bool isKeyDown);
		void on_keyPressed(sdl::Keycode key);
		void meFinishedPlaying(int channel);

		void faderTrigerer();

		void on_fadeCompleate(vas::ScreenManager::FadingState compleatedState);
	private:
		static vas::sreflex::IObjectAutoRegistrar<MainScene> _registrar;

		const std::string me = "assets/audios/me/rain1.ogg";
		std::shared_ptr<vas::Sprite> testSprite{ nullptr };
		std::shared_ptr<vas::Sprite> testSprite2{ nullptr };
		std::shared_ptr<vas::SpriteSheet> testSheet{ nullptr };
		std::shared_ptr<vas::StyledText> textTest{ nullptr };
		bool fadeController{ false };

		vas::Vector2 movement{ 1.0f, 1.0f };
		vas::Vector2 tilePos{ 56, 67 };
	};
}