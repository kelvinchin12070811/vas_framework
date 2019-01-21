#pragma once
#include <deque>
#include <memory>
#include <vasframework/sreflex/ReflectAbleAutoRegistrar.hpp>
#include <vasframework/base/Base.hpp>
#include <vasframework/manager/InputManager.hpp>
#include <vasframework/graphics/sprites/SpriteSheet.hpp>
#include <vasframework/graphics/layer/Layers.hpp>
#include <vasframework/manager/ScreenManager.hpp>
#include <vasframework/graphics/text/StyledText.hpp>
#include <vasframework/graphics/animation/AnimationControllerEx.hpp>
#include <vasframework/graphics/animation/AttrKeyframeAnimation.hpp>
#include "AbstractFrameCountingScene.hpp"

struct OpacityWrap : public vas::AttrWrap<vas::sdl::Colour>
{
	OpacityWrap(std::function<void(vas::sdl::Colour)> mutator, std::function<vas::sdl::Colour()> getter);
	void operator()(double value);
private:
	std::function<vas::sdl::Colour()> getter;
};

namespace scene
{
	class MainScene : public AbstractFrameCountingScene
	{
	public:
		MainScene();
		~MainScene();

		void tick() override;
		void draw() override;

		void afterSceneCall() override;
		void beforeTerminate() override;

		void eventSlot(vas::sdl::Event& ev);
	private:
		//void eventKeyPressHwnd(sdl::Event& ev, bool isKeyDown);
		void on_keyPressed(vas::sdl::Keycode key);
		void meFinishedPlaying(int channel);

		void faderTrigerer();

		void on_fadeCompleate(vas::ScreenManager::FadingState compleatedState);
	private:
		static vas::sreflex::ReflectAbleAutoRegistrar<MainScene> _registrar;

		const std::string me = "assets/audios/me/rain1.ogg";
		std::shared_ptr<vas::Sprite> testSprite{ nullptr };
		std::shared_ptr<vas::Sprite> testSprite2{ nullptr };
		std::shared_ptr<vas::SpriteSheet> testSheet{ nullptr };
		std::shared_ptr<vas::StyledText> textTest{ nullptr };
		bool fadeController{ false };

		vas::Layer rootLayer;
		vas::Vector2 movement{ 1.0f, 1.0f };
		vas::Vector2 tilePos{ 56, 67 };

		vas::AnimationControllerEx animation;

		std::deque<boost::signals2::scoped_connection> conmng;
	};
}