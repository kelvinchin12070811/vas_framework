#pragma once
#include <vasframework/base/Base.hpp>
#include <vasframework/manager/SceneManager.hpp>
#include <vasframework/manager/ScreenManager.hpp>
#include <vasframework/util/CommonTools.hpp>
#include <vasframework/graphics/text/StyledText.hpp>
#include <vasframework/sreflex/Util.hpp>
#include "scenes/MainScene.hpp"
#include "scenes/TileMap.hpp"

class Main
{
public:
	static int main(std::vector<std::string> args);
};

VAS_CLASSLOADER_LOAD(Main)