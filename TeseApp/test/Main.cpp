#include "Main.hpp"
#include "scenes/EmptyScene.hpp"

const bool Main::__launch{ vas::ClassLoader::load<Main>() };

int Main::main(const std::vector<std::string>& args)
{
	VAS_ALLOCATE_CONSOLE;
	vas::CommonTools::getInstance().setConsolePrefix("宮本サクラ");
	try
	{
		vas::Base::getInstance().initAndStartAll("VAS Framework Tester", { 640, 480 }, vas::sdl::Window::Flags::resizable,
			[]() {
				auto textOverlay = std::make_shared<vas::StyledText>("VAS Framework v" + getEngineVersion(),
					"assets/fonts/caladea-regular.ttf", vas::zerovector, 24);
				textOverlay->setStaticOnCamera(true);
				textOverlay->setColour(vas::sdl::ColorPresets::white);
				textOverlay->setBackgroundOffset(vas::Vector2{ 3.0f, vas::Angle{ 45.0 + 90.0 } });
				vas::ScreenManager::getInstance().screenAboveOverlays.insert({ textOverlay });
				vas::SceneManager::getInstance().call("scene::MainScene");
				vas::Base::getInstance().getRenderer().setLogicalSize(vas::sdl::Point{ 640, 480 });
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