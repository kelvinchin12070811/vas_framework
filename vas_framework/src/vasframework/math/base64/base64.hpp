// This is a warpper of ReneNyffenegger's Base64 codec library
#pragma once
#include <string>
#include <vector>
#include "../../VASConfig.hpp"

/** @addtogroup math
	  @{
*/
/** @defgroup base64_lib Base64 Codec
	  @brief The utilities that encode and decode Base64 data.

	  The vas::base64 library are the wrapper of [ReneNyffenegger's Base64 codec library](https://github.com/ReneNyffenegger/cpp-base64)
	  (Licensed under zlib license) with C++ STL Container.

	  This is a very basic codec for the Base64 strings.
*/

/** @} */
namespace vas // extra
{
	namespace base64 // extra
	{
		/** @addtogroup base64_lib
			  @{
		*/
		namespace raw // extra
		{
			/*  The original implementation of Rene's code. Encode an array of bytes to Base64.
				 renamed, std::string base64_encode(unsigned char const* , unsigned int len);
			*/
			VAS_DECLSPEC std::string encode(unsigned char const* bytes_to_encode, unsigned int len);
			/*  The original implementation of Rene's code. Decode a string of Base64 data to bytes array.
				 renamed, std::string base64_decode(std::string const& s);
			*/
			VAS_DECLSPEC std::string decode(std::string const& s);
		}

		/** Encode binary data into Base64 string.
			  @param binaryData Bytes array of raw data.
			  @return Base64 encoded string of the raw data.

			  Wrapped:
			  ```cpp
			  std::string base64_encode(unsigned char const* , unsigned int len);
			  ```
		*/
		VAS_DECLSPEC std::string encode(const std::vector<uint8_t>& binaryData); // extra
		/** Decode Base64 string into bytes array.
			  @param base64Data Base64 string.
			  @return Decoded raw data.

			  Wrapped:
			  ```cpp
			  std::string base64_decode(std::string const& s);
			  ```
		*/
		VAS_DECLSPEC std::vector<uint8_t> decode(const std::string& base64Data); // extra
		/** @} */
	}
}