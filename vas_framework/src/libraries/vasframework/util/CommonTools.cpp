#include "CommonTools.hpp"

namespace vas
{
	CommonTools & CommonTools::getInstance()
	{
		static CommonTools instance;
		return instance;
	}

	CommonTools::CommonTools()
	{
	}

	CommonTools::~CommonTools()
	{
	}
}