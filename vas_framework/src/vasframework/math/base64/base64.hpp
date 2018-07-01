// This is a warpper of Ren?Nyffenegger's Base64 codec library
#pragma once
#include <string>
#include <vector>
#include "../../VASConfig.hpp"

namespace vas // extra
{
	namespace base64 // extra
	{
		namespace raw // extra
		{
			//original code
			VAS_DECLSPEC std::string encode(unsigned char const* bytes_to_encode, unsigned int len); // renamed, std::string base64_encode(unsigned char const* , unsigned int len);
			VAS_DECLSPEC std::string decode(std::string const& s); // renamed, std::string base64_decode(std::string const& s); 
		}

		VAS_DECLSPEC std::string encode(const std::vector<uint8_t>& binaryData); // extra
		VAS_DECLSPEC std::vector<uint8_t> decode(const std::string& base64Data); // extra
	}
}