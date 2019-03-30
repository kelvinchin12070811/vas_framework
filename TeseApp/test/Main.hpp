#pragma once
#include <vasframework/base/Base.hpp>
#include <vasframework/manager/SceneManager.hpp>
#include <vasframework/manager/ScreenManager.hpp>
#include <vasframework/util/CommonTools.hpp>
#include <vasframework/graphics/text/StyledText.hpp>
#include <vasframework/sreflex/Util.hpp>

class Main
{
public:
	static int main(const std::vector<std::string>& args);
private:
	static const bool __launch;
};