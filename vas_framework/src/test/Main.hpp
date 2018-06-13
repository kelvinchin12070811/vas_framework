#pragma once
#include "../libraries/vasframework/base/Base.hpp"
#include "../libraries/vasframework/manager/SceneManager.hpp"
#include "../libraries/vasframework/manager/ScreenManager.hpp"
#include "../libraries/vasframework/util/CommonTools.hpp"
#include "../libraries/vasframework/graphics/text/StyledText.hpp"
#include "../libraries/vasframework/sreflex/Util.hpp"
#include "scenes/MainScene.hpp"
#include "scenes/TileMap.hpp"

class Main
{
public:
	static int main(std::vector<std::string> args);
};

VAS_CLASSLOADER_LOAD(Main)