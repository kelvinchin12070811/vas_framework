// This is a warpper of Ren?Nyffenegger's Base64 codec library

#ifndef COM_BLOGSPOT_KELVINCHIN12070811_VAS_LIBRARIES_BASE64_HPP
#define COM_BLOGSPOT_KELVINCHIN12070811_VAS_LIBRARIES_BASE64_HPP
#include <string>
#include <vector>
namespace vas // extra
{
	namespace base64 // extra
	{
		namespace raw // extra
		{
			//original code
			std::string encode(unsigned char const* bytes_to_encode, unsigned int len); // renamed, std::string base64_encode(unsigned char const* , unsigned int len);
			std::string decode(std::string const& s); // renamed, std::string base64_decode(std::string const& s); 
		}

		std::string encode(const std::vector<uint8_t>& binaryData); // extra
		std::vector<uint8_t> decode(const std::string& base64Data); // extra
	}
}
#endif // !COM_BLOGSPOT_KELVINCHIN12070811_VAS_LIBRARIES_BASE64_HPP