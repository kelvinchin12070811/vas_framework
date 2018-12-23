#pragma once
#include "AbstractFrameCountingScene.hpp"
#include <vasframework/base/Base.hpp>
#include <vasframework/graphics/Camera.hpp>
#include <vasframework/graphics/text/StyledText.hpp>
#include <vasframework/tiledmap/TMXParser.hpp>
#include <vasframework/tiledmap/MapRenderer.hpp>
#include <vasframework/manager/InputManager.hpp>
#include <vasframework/sdlcore/Math.hpp>
#include <vasframework/util/ResourceLoader.hpp>

namespace scene
{
	class TileMap : public AbstractFrameCountingScene
	{
	public:
		TileMap();
		~TileMap();

		void tick() override;
		void draw() override;

		void afterSceneCall() override;
		void beforeTerminate() override;
	private:
		void on_EventPulsed(vas::sdl::Event& ev);
		void on_mouseClicked(vas::sdl::MouseButtonIndex index, vas::sdl::Point position);

	private:
		vas::TMXParser map;
		vas::TilesetsBundle tilesets;
		vas::ResourceLoader loader;

		std::vector<boost::signals2::connection> signalsPool;
		std::vector<std::shared_ptr<vas::MapRenderer>> mapLayers{ nullptr };
	private:
		static const vas::sreflex::ReflectAbleAutoRegistrar<TileMap> __REGISTRAR;
	};
}