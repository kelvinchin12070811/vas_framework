#include "NotImplementedException.hpp"

namespace vas
{
	const char * NotImplementedException::what() const
	{
		return "An unimplemented function is called";
	}
}