#include "../libraries/vasframework/base/Base.hpp"
#include "../libraries/vasframework/manager/SceneManager.hpp"
#include "../libraries/vasframework/manager/ScreenManager.hpp"
#include "../libraries/vasframework/util/CommonTools.hpp"
#include "../libraries/vasframework/graphics/text/StyledText.hpp"
#include "../libraries/vasframework/sreflex/Util.hpp"
#include "scenes/MainScene.hpp"
#include "scenes/TileMap.hpp"

//int main(int argc, char** argv)
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR cmdLine, int cmdShow)
{
	AllocConsole();
	freopen("CONIN$", "r+t", stdin);
	freopen("CONIN$", "w+t", stdout);

	vas::CommonTools::getInstance().setAssistanceName("宮本サクラ");
	try
	{
		vas::Base::getInstance().initAndStartAll("VAS Framework Tester", sdl::Point(640, 480), sdl::Window::Flags::shown, []() {
			auto textOverlay = std::make_shared<vas::StyledText>("VAS Framework v2.0 indev", "assets/fonts/caladea-regular.ttf", vas::zerovector, 24);
			textOverlay->setColour(sdl::ColorPresets::white);
			textOverlay->setBackgroundOffset(vas::Vector2(3.0f, ANGLE_FROM_SECOND_QUATER(45.0)));
			textOverlay->setStaticOnCamera(true);
			vas::ScreenManager::getInstance().screenAboveOverlays.insert(VAS_INSERT_VAR(textOverlay));
			vas::SceneManager::getInstance().call(std::make_shared<scene::TileMap>());
		});
	}
	catch (const std::exception& e)
	{
		vas::Err() << "exception occur, " << vas::sreflex::getObjectNameRuntime(e) << ": " << e.what();
		vas::Base::getInstance().cleanAndQuit();
		//return vas::CommonTools::getInstance().messenger(e.what(), vas::CommonTools::MessageType::error, -1);
		return -1;
	}

	return 0;
}