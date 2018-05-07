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
		using namespace std::chrono_literals;
		CommonTools::getInstance().messenger("Scene " + sreflex::getObjectName<TileMap>() + " is called");
		InputManager::getInstance().mouseButtonPressed.connect(boost::bind(&TileMap::on_mouseClicked, this, _1, _2, _3));
		engineName = std::make_shared<StyledText>("VAS Framework v2.0 indev", "assets/fonts/caladea-regular.ttf", zerovector, 12);
		engineName->setBackgroundOffset(Vector2(3.0f, Angle(45.0 + 90.0)));

		map.load("assets/maps/animated map.tmx");

		CallRenderAssistance;
		RenderAssistance->insert(VAS_INSERT_VAR(engineName));
		auto bgm = *map.getMapProperties().customProperties["startup bgm"].get<std::string>();
		boost::replace_all(bgm, "../", "assets/");
		AudioManger::getInstance().playBGM(bgm, 500ms);
	}

	void TileMap::Signal_beforeTerminate()
	{
		InputManager::getInstance().mouseButtonPressed.disconnect(boost::bind(&TileMap::on_mouseClicked, this, _1, _2, _3));
	}

	void TileMap::on_EventPulsed(sdl::Event & ev)
	{
	}

	void TileMap::on_mouseClicked(vas::MouseButtonIndex index, int x, int y)
	{
		switch (index)
		{
		case SDL_BUTTON_LEFT:
			vas::CommonTools::getInstance().messenger((boost::format("Mouse left clicked at: %i , %i") % x % y).str());
			break;
		}
	}
}