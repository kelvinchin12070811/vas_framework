#pragma once
#include "AbstractFrameCountingScene.hpp"
#include <vasframework/base/Base.hpp>
#include <vasframework/graphics/Camera.hpp>
#include <vasframework/graphics/text/StyledText.hpp>
#include <vasframework/tiledmap/TMXParser.hpp>
#include <vasframework/tiledmap/MapRenderer.hpp>
#include <vasframework/manager/InputManager.hpp>

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
		void on_EventPulsed(vas::sdl::Event& ev);
		void on_mouseClicked(vas::MouseButtonIndex index, int x, int y);

	private:
		vas::TMXParser map;
		vas::TilesetsBundle tilesets;

		std::vector<boost::signals2::connection> signalsPool;
		std::vector<std::shared_ptr<vas::MapRenderer>> mapLayers{ nullptr };
	};
}