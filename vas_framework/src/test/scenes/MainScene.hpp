#pragma once
#include "../../libraries/vasframework/graphics/scene/SceneBase.hpp"
#include "../../libraries/vasframework/sreflex/IObjectAutoRegistrar.h"
#include "../../libraries/vasframework/base/Base.hpp"

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
		static vas::sreflex::IObjectAutoRegistrar<MainScene> _registrar;

		sdl::mixer::Music bgm;
		sdl::mixer::Chunk me{ 1 };
		sdl::Texture testTexture;
		sdl::Rect testRect;
	};
}