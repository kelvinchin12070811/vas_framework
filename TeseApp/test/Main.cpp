#include "Main.hpp"
#include "scenes/EmptyScene.hpp"

const bool Main::__launch{ vas::ClassLoader::load<Main>() };

int Main::main(const std::vector<std::string>& args)
{
	VAS_ALLOCATE_CONSOLE;
	//vas::CommonTools::getInstance().setAssistanceName("宮本サクラ");
	try
	{
		{ //Call stack memory management test.
			vas::Log() << "Before: " << vas::SceneManager::getInstance().capacity();

			for (int loop{ 0 }; loop < 10; loop++)
				vas::SceneManager::getInstance().emplaceCall<scene::EmptyScene>();

			vas::Log() << "Emulated 10 scenes called: " << vas::SceneManager::getInstance().capacity();

			for (int loop{ 0 }; loop < 30; loop++)
				vas::SceneManager::getInstance().emplaceCall<scene::EmptyScene>();

			vas::Log() << "Emulated 30 scenes called: " << vas::SceneManager::getInstance().capacity();

			for (int loop{ 0 }; loop < 40; loop++)
				vas::SceneManager::getInstance().back();
			vas::Log() << "Emulated scenes cleared returned: " << vas::SceneManager::getInstance().capacity();
			vas::Log() << "current  call count: " << vas::SceneManager::getInstance().instanceCount();
		}
		vas::Base::getInstance().initAndStartAll("VAS Framework Tester", { 640, 480 }, vas::sdl::Window::Flags::resizable, []() {
			auto textOverlay = std::make_shared<vas::StyledText>("VAS Framework v" + getEngineVersion(), "assets/fonts/caladea-regular.ttf", vas::zerovector, 24);
			textOverlay->setStaticOnCamera(true);
			textOverlay->setColour(vas::sdl::ColorPresets::white);
			textOverlay->setBackgroundOffset(vas::Vector2{ 3.0f, ANGLE_FROM_SECOND_QUATER(45.0) });
			vas::ScreenManager::getInstance().screenAboveOverlays.insert(VAS_INSERT_VAR(textOverlay));
			vas::SceneManager::getInstance().call("scene::NBTTreeTest");
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