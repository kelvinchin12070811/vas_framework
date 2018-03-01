#pragma once
#include <memory>
#include "../../libraries/vasframework/sreflex/IObjectAutoRegistrar.hpp"
#include "../../libraries/vasframework/base/Base.hpp"
#include "../../libraries/vasframework/manager/InputManager.hpp"
#include "../../libraries/vasframework/graphics/sprites/SpriteSheet.hpp"
#include "AbstractFrameCountingScene.hpp"

namespace scene
{
	class MainScene : public AbstractFrameCountingScene
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
		void eventKeyPressHwnd(sdl::Event& ev, bool isKeyDown);
		void meFinishedPlaying(int channel);
		static vas::sreflex::IObjectAutoRegistrar<MainScene> _registrar;

		const std::string me = "assets/audios/me/rain1.ogg";
		std::shared_ptr<vas::Sprite> testSprite{ nullptr };
		std::shared_ptr<vas::SpriteSheet> testSheet{ nullptr };
	};
}