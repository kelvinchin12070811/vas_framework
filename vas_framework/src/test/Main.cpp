#include "Main.hpp"

int Main::main(std::vector<std::string> args)
{
	VAS_ALLOCATE_CONSOLE;
	vas::CommonTools::getInstance().setAssistanceName("宮本サクラ");
	try
	{
		vas::Base::getInstance().initAndStartAll("VAS Framework Tester", vas::sdl::Point(1280, 720), vas::sdl::Window::Flags::resizable, []() {
			auto textOverlay = std::make_shared<vas::StyledText>("VAS Framework v" + getEngineVersion(), "assets/fonts/caladea-regular.ttf", vas::zerovector, 24);
			textOverlay->setColour(vas::sdl::ColorPresets::white);
			textOverlay->setBackgroundOffset(vas::Vector2(3.0f, ANGLE_FROM_SECOND_QUATER(45.0)));
			//textOverlay->setStaticOnCamera(true);
			vas::ScreenManager::getInstance().screenAboveOverlays.insert(VAS_INSERT_VAR(textOverlay));
			vas::SceneManager::getInstance().call(std::make_shared<scene::TileMap>());

			vas::Base::getInstance().Renderer().setLogicalSize(vas::sdl::Point(640, 480));
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