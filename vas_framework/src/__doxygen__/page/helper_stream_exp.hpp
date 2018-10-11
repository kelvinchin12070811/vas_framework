/** @page helper_stream_exp Helper stream examples

	  ## Basic usage
	  ~~~cpp
	  #include <vasframework/util/TextTools.hpp>

	  int main()
	  {
		  vas::Cout() << "Output to vas::Cout" << std::endl;
		  vas::Ceer() << "Output to vas::Ceer" << std::endl;

		  int value = 0;
		  vas::Cin() >> value; //Read from vas::Cin

		  vas::Cout::getWrapedStream() << L"Get the native wrapped stream, in this case std::wcout" << std::endl;

		  vas::Cout::getBuffer() = std::stringstream(); //Clear the internal buffer and reset manipulator by swapping its stringstream.

		  return 0;
	  }
	  ~~~
*/