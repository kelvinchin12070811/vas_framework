/**
 * @page getstart Getting Started Guide
 * This guide is  to guide new user in basic usage of the library. To proceed, The basic of SDL and using a compiled
 * library is needed.
 * 
 * ### Download Virtual Asistant Framework and other required libraries.
 * 
 * Download the library here [https://github.com/kelvinchin12070811/vas_framework](https://github.com/kelvinchin12070811/vas_framework).
 * Clone and download the entire repository in zip, compilition of the library is not needed.
 * 
 * Besides than the main library it self, some of the other libraries are required to support the vas_framework. The other
 * requied libraries that this guide will use are shown as bellow.
 * 
 *  -# SDL2 - [http://www.libsdl.org](http://www.libsdl.org)
 *  -# SDL_image - [http://www.libsdl.org/projects/sdl_image](http://www.libsdl.org/projects/sdl_image)
 *  -# SDL_mixer - [http://www.libsdl.org/projects/sdl_mixer](http://www.libsdl.org/projects/sdl_mixer)
 *  -# SDL_ttf - [http://www.libsdl.org/projects/sdl_ttf](http://www.libsdl.org/projects/sdl_ttf)
 *  -# Boost C++ library - [http://www.boost.org](http://www.boost.org)
 * 
 *  For other libraries please refer to [Required external libraries](extlibs.html).
 * 
 *  Unzip all of those library and place them at some where on the hard drive.
 * 
 *  ### Add the library to the project.
 *  
 *  To add the Virtual Assistant Framework into a project, copy the "vasframework" folder from "vas_framework/src"
 *  under the downloaded framework's folder to the project folder.
 * 
 *  Next, link the external libraries to the project's "Additional include path" and "Additional library dependecy" if it is
 *  not a header only library. For boost library, the path is setted to the root of the SDK folder. The path to include can
 *  refer to [Required external libraries](extlibs.html).
 * 
 *  ### Start writing code.
 * 
 *  By default, Virtual Assistant Framework use [Object-oriented Entry point](ooentry.html) which define the main
 *  function like Java or C#. The class that contain main function which called as "launcher class" in the library. The
 *  launcher class is then registered and loaded using class loader and it's main function is called.
 * 
 *  The launcher class must have one public static member function called main with constant reference to a std::vector
 *  of std::string. Virtual Assistant Framework use std::vector as the container of command line arguments because it
 *  have more functionality than a pure C array such as iterate over the container with begin() and end().
 *  
 *  ~~~cpp
 *  class Launcher
 *  {
 * public:
 * 	static int main(const std::vector<std::string>& args); // Note this is a public static member
 *  }
 *  ~~~
 * 
 *  The launcher class is then registered via vas::ClassLoader::load() function as bellow:
 * 
 *  ~~~cpp
 *  #include "vasframework/base/Base.hpp" // Header for vas::ClassLoader
 * 
 *  class Launcher
 *  {
 *  public:
 * 	static int main(const std::vector<std::string>& args); // Note this is a public static member
 * private:
 * 	static const bool __launch{ vas::ClassLoader::load<Launcher>() };
 *  }
 *  ~~~
 * 
 *  The ClassLoader's load function is called to register the launcher class, call to initialize a static variable make sure it
 *  run before the program start. All of user defined code are start from the main member function.
 * 
 * @note A project might contain more than one launcher class but make sure __ONLY ONE__ launcher class is
 * registered.
 * 
 * To begin with new project, include the header "vasframework/base/Base.hpp" (or other similar relative path to
 * Base.hpp) and define the launcher class as bellow.
 * 
 * ~~~cpp
 * //Launcher.cpp
 * #include "vasframework/base/Base.hpp"
 * 
 * class Launcher
 * {
 * public:
 * 	static int main(const std::vector<std::string>& args)
 * 	{
 * 		return 0;
 * 	}
 * private:
 * 	static bool __launch{ vas::ClassLoader::load<Launcher>() };
 * }
 * ~~~
 * 
 * Next, we need to initialize and start the framework. The esiest way to do this is tell the vas::Base instance to initialize
 * it. Therefore, in the main function we added:
 * 
 * ~~~cpp
 * vas::Base::getInstance().initAndStartAll("First window", { 640, 480 }, vas::sdl::Window::Flags::shown);
 * ~~~
 * 
 * The vas::Base::initAndStartAll function accept 3 and 1 optional parameters. The first one is the title of the window,
 * second is a vas::sdl::Point of value that represented as the size of the window. The third one is the sdl flags that use to
 * create the window (refer to vas::sdl::Window::Flags). The fourth parameter is the function object in std::function of
 * void() that called before the game loop is run, it usually use to initialize the framework before the game loop start.
 * 
 * Compile and run the application and now a window will poped. Virtual Assistant Framework manage the window and
 * the game loop by it self therefore self manage it is not needed. The application will quit when the window closed and
 * make sure all of the allocated memory and loaded libraries used by vas_framework are freed.
 * 
 * You can also manually initialize the library, but you need to allocate Window and Renderer manually also.
 * 
 * ~~~cpp
 * vas::Base::getInstance().init(); // Initialize sdl library.
 * vas::sdl::Window window("First window",
 * 	{ vas::sdl::Window::DefValues::posCentered, vas::sdl::Window::DefValues::posCentered },
 * 	{ 640, 480 }, vas::sdl::Window::Flags::shown);
 * vas::sdl::Renderer renderer(window, -1, vas::sdl::Renderer::RendererFlags::accelerated);
 * 
 * // Create and assign window and renderer.
 * vas::Base::getInstance().setWindow(std::move(window));
 * vas::Base::getInstance().setRenderer(std::move(renderer));
 * 
 * vas::Base::getInstance().startGameLoop(); // Start main game loop.
 * vas::Base::getInstance().cleanAndQuit(); // Clean all and exit.
 * ~~~
 */