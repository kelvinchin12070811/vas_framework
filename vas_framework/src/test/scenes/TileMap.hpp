#pragma once
#include "AbstractFrameCountingScene.hpp"
#include "../../libraries/vasframework/base/Base.hpp"
#include "../../libraries/vasframework/graphics/text/StyledText.hpp"
#include "../../libraries/vasframework/tiledmap/TMXParser.hpp"
#include "../../libraries/vasframework/manager/InputManager.hpp"

namespace scene
{
	class TileMap : public AbstractFrameCountingScene
	{
	public:
		TileMap();
		~TileMap();

		void tick() override;
		void draw() override;

		void Signal_afterSceneCall() override;
		void Signal_beforeTerminate() override;
	private:
		void on_EventPulsed(sdl::Event& ev);
		void on_mouseClicked(vas::MouseButtonIndex index, int x, int y);

	private:
		std::shared_ptr<vas::StyledText> engineName{ nullptr };
		vas::TMXParser map;
	};
}