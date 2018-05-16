#include <sstream>
#include <filesystem>
#include <boost/algorithm/string.hpp>
#include "TileMap.hpp"
#include "../../libraries/vasframework/util/CommonTools.hpp"
#include "../../libraries/vasframework/manager/AudioManger.hpp"
#include "../../libraries/vasframework/sreflex/Util.hpp"

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
		AbstractFrameCountingScene::tick();
	}

	void TileMap::draw()
	{
		AbstractFrameCountingScene::draw();
	}

	void TileMap::Signal_afterSceneCall()
	{
		using namespace std::experimental;
		using namespace std::chrono;
		vasout << "Scene " << sreflex::getObjectName<TileMap>() << " is called";

		signalsPool.push_back(InputManager::getInstance().mouseButtonPressed.connect(boost::bind(&TileMap::on_mouseClicked, this, _1, _2, _3)));

		engineName = std::make_shared<StyledText>("VAS Framework v2.0 indev", "assets/fonts/caladea-regular.ttf", zerovector, 24);
		engineName->setColour(sdl::ColourPresets::white);
		engineName->setBackgroundColour(sdl::ColourPresets::red);
		engineName->setBackgroundOffset(Vector2(3.0f, ANGLE_FROM_SECOND_QUATER(45.0)));

		map.load("assets/maps/animated map.tmx");

		CallRenderAssistance;
		RenderAssistance->insert(VAS_INSERT_VAR(engineName));
		auto bgm = *map.getMapProperties().customProperties["startup bgm"].get<std::string>();

		filesystem::path bgmPath = *map.getMapProperties().customProperties["startup bgm"].get<std::string>();
		filesystem::path assetsPath = filesystem::current_path() / "assets/maps";

		vasout << bgmPath;
		vasout << assetsPath;
		vasout << filesystem::absolute(bgmPath, assetsPath);

		//AudioManger::getInstance().playBGM(bgmPath.generic_string(), 500ms);
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
			vasout << vasformat("Mouse left clicked at: %i, %i") % x % y;
			break;
		}
	}
}