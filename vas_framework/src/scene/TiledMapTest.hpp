#pragma once
#include <memory>
#include <Windows.h>
#include "../libraries/VASFramework/graphics/scene/SceneBase.hpp"
#include "../libraries/VASFramework/base/EventHandler.hpp"
#include "../libraries/VASFramework/manager/FadingManager.hpp"
#include "../libraries/tmxpraser/TMXPraser.hpp"
#include "../libraries/tmxpraser/containeres/MapRenderer.hpp"
#include "../libraries/VASFramework/containers/Boolean.hpp"

using namespace std::string_literals;

namespace scene
{
	class TiledMapTest : public vas::SceneBase, public vas::EventHandler
	{
	public:
		TiledMapTest();
		~TiledMapTest();

		void tick() override;
		void draw() override;

		void eventSlot(SDL_Event& eventBus) override;
	private:
		std::shared_ptr<vas::TMXPraser> map = nullptr;
		std::vector<vas::Boolean> colisionData;
	};
}