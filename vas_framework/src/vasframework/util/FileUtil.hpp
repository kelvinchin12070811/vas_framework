#pragma once
#include <fstream>
#include <sstream>
#include <vector>

namespace vas
{
	inline std::stringstream readAll(std::istream& stream)
	{
		std::stringstream ss;
		ss << stream.rdbuf();
		return ss;
	}

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

	inline std::stringstream readAll(const std::string& fileName)
	{
		std::ifstream input;
		input.open(fileName);
		if (!input.is_open())
			return std::stringstream();
		return readAll(input);
	}

	inline std::vector<uint8_t> readAllBinary(const std::string& fileName)
	{
		std::ifstream input;
		input.open(fileName, std::ios::binary);
		if (!input.is_open())
			return std::vector<uint8_t>();
		return readAllBinary(input);
	}
}