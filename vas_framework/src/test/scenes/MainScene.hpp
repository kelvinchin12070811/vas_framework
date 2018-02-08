#pragma once
#include "../../libraries/vasframework/graphics/scene/SceneBase.hpp"
#include "../../libraries/vasframework/sreflex/IObjectAutoRegistrar.h"
#include "../../libraries/vasframework/base/Base.hpp"
#include "../../libraries/vasframework/manager/InputManager.hpp"

namespace scene
{
	class MainScene : public vas::SceneBase
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

		static vas::sreflex::IObjectAutoRegistrar<MainScene> _registrar;

		sdl::mixer::Music bgm;
		sdl::mixer::Chunk me{ 1 };
		sdl::Texture testTexture;
		sdl::Rect testRect;
		sdl::Point center;
		double angle = 0;
	};
}