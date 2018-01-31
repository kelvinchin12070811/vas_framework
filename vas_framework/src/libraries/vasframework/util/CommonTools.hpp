#pragma once
#include "TextTools.hpp"

namespace vas
{
	class CommonTools
	{
	public:
		static CommonTools& getInstance();

		bool hasConsole = false;
	private:
		CommonTools();
		~CommonTools();
	};
}