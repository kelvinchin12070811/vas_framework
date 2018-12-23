 #include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <vasframework/util/CommonTools.hpp>
#include <vasframework/manager/AudioManger.hpp>
#include <vasframework/manager/ScreenManager.hpp>
#include <vasframework/sreflex/Util.hpp>
#include <vasframework/tiledmap/container/TilesetsBundle.hpp>
#include <vasframework/container/nbt/CommonTag.hpp>
#include <vasframework/math/Clock.hpp>
#include <vasframework/util/CommonTools.hpp>
#include "TileMap.hpp"

using namespace vas;
using namespace boost::placeholders;

namespace scene
{
	const sreflex::ReflectAbleAutoRegistrar<TileMap> TileMap::__REGISTRAR{};
	TileMap::TileMap()
	{
		Int32Tag tag = 35;
		tag += 45;

		NBTCompoundTag root;
		auto player = std::make_shared<NBTCompoundTag>();
		player->insert("position", std::make_shared<Vector2Tag>(Vector2(64.0f, 48.0f)));
		root.insert("player", player);

		loader.load({
				std::make_unique<vas::resource_type::Texture>("assets/textures/639098.jpg"),
				std::make_unique<vas::resource_type::Music>("assets/audios/bgm/Get_Outside.mp3")
			});
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
		auto camPos = vas::Camera::getInstance().getPosition();
		camPos.x = std::clamp(camPos.x, 0.0f, static_cast<float>(map.getMapSize().w() - Camera::getInstance().getSize().w()));
		camPos.y = std::clamp(camPos.y, 0.0f, static_cast<float>(map.getMapSize().h() - Camera::getInstance().getSize().h()));
		Camera::getInstance().setPosition(camPos);

		tilesets.tick();
		AbstractFrameCountingScene::tick();
	}

	void TileMap::draw()
	{
		AbstractFrameCountingScene::draw();
	}

	void TileMap::afterSceneCall()
	{
		using namespace std::chrono;
		vas::Log() << "Scene " << sreflex::getObjectName<TileMap>() << " is called";

		vas::Cout() << "Test raw output with endl" << std::endl;
		vas::Cout() << "Another raw output with unicode word 宮本桜" << std::endl;

		signalsPool.push_back(InputManager::getInstance().MouseButtonPressed.connect(boost::bind(&TileMap::on_mouseClicked, this, _1, _2)));

		map.load("assets/maps/animated map.tmx");

		CallRenderAssistance;
		auto bgm = *map.getMapProperties().customProperties["startup bgm"].get<std::string>();

		boost::filesystem::path bgmPath = *map.getMapProperties().customProperties["startup bgm"].get<std::string>();
		boost::filesystem::path assetsPath = boost::filesystem::current_path() / "assets/maps";
		bgmPath = boost::filesystem::absolute(bgmPath, assetsPath).normalize().make_preferred();
		AudioManager::getInstance().playBGM(bgmPath.string(), 500ms);

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
	}

	void TileMap::beforeTerminate()
	{
		for (auto& itr : signalsPool)
			itr.disconnect();
	}

	void TileMap::on_EventPulsed(vas::sdl::Event & ev)
	{
	}

	void TileMap::on_mouseClicked(sdl::MouseButtonIndex index, sdl::Point position)
	{
		switch (index)
		{
		case sdl::MouseButtonIndex::ButtonLeft:
			//vas::CommonTools::getInstance().messenger((boost::format("Mouse left clicked at: %i , %i") % x % y).str());
			vas::Log() << boost::format("Mouse left clicked at: %i, %i") % position.x % position.y;
			break;
		}
	}
}