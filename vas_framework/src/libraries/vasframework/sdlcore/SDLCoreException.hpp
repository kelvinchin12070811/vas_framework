#pragma once
#include <exception>
#include "../VASConfig.hpp"

namespace sdl
{
	class VAS_DECLSPEC SDLCoreException : public std::exception
	{
	public:
		SDLCoreException();
		~SDLCoreException();
		char const* what() const override;
	};
}