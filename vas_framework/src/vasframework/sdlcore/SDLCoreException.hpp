#pragma once
#include <exception>
#include "../VASConfig.hpp"

namespace vas::sdl
{
	class VAS_DECLSPEC SDLCoreException : public std::exception
	{
	public:
		SDLCoreException();
		~SDLCoreException();
		char const* what() const override;
	};
}