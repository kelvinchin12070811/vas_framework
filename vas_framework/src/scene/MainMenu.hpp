#pragma once
#include "../libraries/VASFramework/graphics/scene/SceneBase.hpp"
#include "../libraries/VASFramework/base/EventHandler.hpp"
#include "../libraries/VASFramework/util/CommonTools.hpp"
#include "../libraries/VASFramework/util/TextTools.hpp"
#include "../libraries/VASFramework/base/Base.hpp"
#include "../libraries/VASFramework/graphics/sprites/sprite/Sprite.hpp"
#include "../libraries/VASFramework/graphics/sprites/spritesheet/SpriteSheet.hpp"
#include "../libraries/VASFramework/graphics/text/Text.hpp"
#include "../libraries/VASFramework/manager/FadingManager.hpp"

namespace scene
{
	class MainMenu : public vas::SceneBase, public vas::EventHandler
	{
	public:
		MainMenu();
		~MainMenu();

		void tick() override;
		void draw() override;

		void eventSlot(SDL_Event& eventBus);
		void Signal_afterSceneCall();
	private:
		std::shared_ptr<vas::SpriteSheet> someSprite = nullptr;
		std::shared_ptr<vas::Sprite> background = nullptr;
		std::shared_ptr<vas::Text> someText = nullptr;
		bool dash = false;
	};
}