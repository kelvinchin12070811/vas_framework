#pragma once
#include <stdexcept>
#include "../VASConfig.hpp"

namespace vas
{
	class VAS_DECLSPEC NotImplementedException : public std::exception
	{
	public:
		NotImplementedException();
		~NotImplementedException();
		const char* what() const override;
	};
}