//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
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