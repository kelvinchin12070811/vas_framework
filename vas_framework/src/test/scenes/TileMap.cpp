#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include "TileMap.hpp"
#include "../../libraries/vasframework/util/CommonTools.hpp"
#include "../../libraries/vasframework/manager/AudioManger.hpp"
#include "../../libraries/vasframework/sreflex/Util.hpp"
#include "../../libraries/vasframework/tiledmap/container/TilesetsBundle.hpp"

using namespace vas;
using namespace boost::placeholders;

namespace scene
{
	TileMap::TileMap()
	{
	}

	TileMap::~TileMap()
	{
	}

	void TileMap::tick()
	{
		{ // Input area
			vas::Vector2 camMovement;
			if (vas::InputManager::getInstance().isKeyTriggered(sdl::Scancode::up))
				camMovement.y = -1;
			else if (vas::InputManager::getInstance().isKeyTriggered(sdl::Scancode::down))
				camMovement.y = 1;

			if (vas::InputManager::getInstance().isKeyTriggered(sdl::Scancode::left))
				camMovement.x = -1;
			else if (vas::InputManager::getInstance().isKeyTriggered(sdl::Scancode::right))
				camMovement.x = 1;

			if (vas::InputManager::getInstance().isKeyTriggered(sdl::Scancode::lshift))
				camMovement *= 4;

			vas::Camera::getInstance().move(camMovement);
		}

		tilesets.tick();
		AbstractFrameCountingScene::tick();
	}

	void TileMap::draw()
	{
		AbstractFrameCountingScene::draw();
	}

	void TileMap::Signal_afterSceneCall()
	{
		using namespace std::chrono;
		vas::Log() << "Scene " << sreflex::getObjectName<TileMap>() << " is called";

		signalsPool.push_back(InputManager::getInstance().mouseButtonPressed.connect(boost::bind(&TileMap::on_mouseClicked, this, _1, _2, _3)));

		engineName = std::make_shared<StyledText>("VAS Framework v2.0 indev", "assets/fonts/caladea-regular.ttf", zerovector, 24);
		engineName->setColour(sdl::ColourPresets::white);
		engineName->setBackgroundColour(sdl::ColourPresets::red);
		engineName->setBackgroundOffset(Vector2(3.0f, ANGLE_FROM_SECOND_QUATER(45.0)));

		map.load("assets/maps/animated map.tmx");

		CallRenderAssistance;
		auto bgm = *map.getMapProperties().customProperties["startup bgm"].get<std::string>();

		boost::filesystem::path bgmPath = *map.getMapProperties().customProperties["startup bgm"].get<std::string>();
		boost::filesystem::path assetsPath = boost::filesystem::current_path() / "assets/maps";
		bgmPath = boost::filesystem::absolute(bgmPath, assetsPath).normalize().make_preferred();
		AudioManger::getInstance().playBGM(bgmPath.string(), 500ms);

		for (auto& itr : const_cast<std::vector<vas::Tileset>&>(map.getRequireTilesets()))
		{
			boost::filesystem::path path = boost::filesystem::absolute(itr.source.name, assetsPath).normalize().make_preferred();
			itr.source.name = path.string();
		}

		tilesets.load(map.getRequireTilesets(), map.getMapProperties().tileWidth, map.getMapProperties().tileHeight);

		for (auto& itr : map.getMapData())
		{
			if (itr->getName() == "$!collisions") continue;
			if (auto layerData = dynamic_cast<vas::TileLayer*>(itr.get()); layerData != nullptr)
			{
				mapLayers.push_back(std::make_shared<vas::MapRenderer>(layerData,
					sdl::Point(map.getMapProperties().mapWidth, map.getMapProperties().mapHeight),
					sdl::Point(map.getMapProperties().tileWidth, map.getMapProperties().tileHeight),
					tilesets));
			}
		}
		
		for (size_t index = 0; index < mapLayers.size(); index++)
		{
			RenderAssistance->insert(VAS_LAYER_DATA("map layer " + boost::lexical_cast<std::string>(index), mapLayers[index]));
		}
		RenderAssistance->insert(VAS_INSERT_VAR(engineName));
	}

	void TileMap::Signal_beforeTerminate()
	{
		for (auto& itr : signalsPool)
			itr.disconnect();
	}

	void TileMap::on_EventPulsed(sdl::Event & ev)
	{
	}

	void TileMap::on_mouseClicked(vas::MouseButtonIndex index, int x, int y)
	{
		switch (index)
		{
		case SDL_BUTTON_LEFT:
			//vas::CommonTools::getInstance().messenger((boost::format("Mouse left clicked at: %i , %i") % x % y).str());
			vas::Log() << boost::format("Mouse left clicked at: %i, %i") % x % y;
			break;
		}
	}
}