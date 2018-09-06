/*! \page uni_entry Uniform Entry
	 Uniform Entry Point provide a cross-platform way to implement entry point of a program.
	 VAS Framework will load a class with a public static member function named main which called "Launcher Class"
	 when the program start.

	 The launcher class __must have one and only public main function with the following signature__

	 ```cpp
	 static int main(std::vector<std::string> args); // Note this function should be a public member.
	 ```

	 The arguments are passed as an object of std::vector so it can be benifit from dynamic "smart" array.

	 After all of the work is done, the macro `#VAS_CLASSLOADER_LOAD` is used to loadup the class and start the program.

	 Example:
	 ```cpp
	 // Launcher.hpp
	 #include <vasframework/base/Base.hpp>

	 class Launcher
	 {
		public:
			static int main(std::vector<std::string> args) // This is the main function which will be loaded using class loader.
			{
				// do something...
				return 0;
			}
	 }

	 VAS_CLASSLOADER_LOAD(Launcher);
	 ```
*/