#include "Util.hpp"

namespace vas
{
	namespace sreflex
	{
		void simpliflyObjectName(std::string & input)
		{
			if (input.find("class ") == 0)
				input = input.substr(6);
		}

		std::string simpliflyObjectNameCpy(const std::string & input)
		{
			if (input.find("class ") == 0)
				return input.substr(6);
			else return input;
		}
	}
}