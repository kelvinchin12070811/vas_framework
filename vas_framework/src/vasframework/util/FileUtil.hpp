#pragma once
#include <fstream>
#include <sstream>
#include <vector>

/** @addtogroup util
	  @{
*/
/** @defgroup file_util Files Utilities
	  @brief Tools that help user to work with files.
*/
/** @} */
namespace vas
{
	/** @addtogroup file_util
		  @{
	*/

	/** Read all content of an istream.
		  @param stream Input stream.
		  @retval std::stringstream All content of the @p stream.
	*/
	inline std::stringstream readAll(std::istream& stream)
	{
		std::stringstream ss;
		ss << stream.rdbuf();
		return ss;
	}
	/** Read all binary content of an istream.
		  @param stream Input stream.
		  @retval std::vector<uint8_t> Binary content of stream.
	*/
	inline std::vector<uint8_t> readAllBinary(std::istream& stream)
	{
		size_t fileSize = 0;
		stream.seekg(std::istream::end);
		fileSize = stream.tellg();
		stream.seekg(std::istream::beg);
		std::vector<uint8_t> bin(fileSize);
		stream.read(reinterpret_cast<char*>(bin.data()), fileSize);
		return bin;
	}

	/** Open and read all content of a file.
		  @param fileName Name or path to the target file.
		  @retval std::stringstream Content of @p fileName if success, empty if failed.
	*/
	inline std::stringstream readAll(const std::string& fileName)
	{
		std::ifstream input;
		input.open(fileName);
		if (!input.is_open())
			return std::stringstream();
		return readAll(input);
	}

	/** Open and read all binary content of a file.
		  @param fileName Name of path to the target file.
		  @retval std::vector<uint8_t> Binary content of @p fileName.
	*/
	inline std::vector<uint8_t> readAllBinary(const std::string& fileName)
	{
		std::ifstream input;
		input.open(fileName, std::ios::binary);
		if (!input.is_open())
			return std::vector<uint8_t>();
		return readAllBinary(input);
	}
	/** @} */
}