#include "NotImplementedException.hpp"

namespace vas
{
	NotImplementedException::NotImplementedException()
	{
	}

	NotImplementedException::~NotImplementedException()
	{
	}

	const char * NotImplementedException::what() const
	{
		return "An unimplemented function is called";
	}
}