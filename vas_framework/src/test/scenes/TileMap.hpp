#pragma once
#include "AbstractFrameCountingScene.hpp"
#include "../../libraries/vasframework/base/Base.hpp"
#include "../../libraries/vasframework/graphics/text/StyledText.hpp"
#include "../../libraries/vasframework/tiledmap/TMXParser.hpp"

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
	private:
		std::shared_ptr<vas::StyledText> engineName{ nullptr };
		vas::TMXParser map;
	};
}