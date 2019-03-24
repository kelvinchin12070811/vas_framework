/**
 * @page ooentry Object-oriented Entry Point
 * object-oriented Entry Point provide a way to implement entry point of a program with the benifit of OOP.
 * VAS Framework will load a class with a public static member function named main which called "Launcher Class"
 * when the program start.
 * 
 * The launcher class __must have one and only public main function with the following signature__
 * 
 * ```cpp
 * static int main(const std::vector<std::string>& args); // Note this function should be a public member.
 * ```
 * 
 * The arguments are passed as an object of std::vector so it can be benifit from the std::vector which have lot more
 * function to access the array.
 * 
 * After all of the work is done, the class vas::ClassLoader is used to load up the class and start the program. The
 * ClassLoader will then initialize the static bool member variable (can be constant) with member function
 * vas::ClassLoader::load() and start the program with the specified Launcher class.
 *  
 * Example:
 * ```cpp
 * // Launcher.hpp
 * #include <vasframework/base/Base.hpp>
 * 
 * class Launcher
 * {
 * public:
 *		static int main(const std::vector<std::string>& args); // This is the main function which will be loaded using class loader.
 * private:
 *		static const bool __launch;
 * }
 * 
 * // Launcher.cpp
 * #include "Launcher.hpp"
 *const bool Launcher::__launch{ vas::ClassLoader::load<Launcher>() };
 *
 * int Launcher::main(const std::vector<std::string>& args)
 * {
 *		//do somethings.
 *		return 0;
 * }
 * ```
 */