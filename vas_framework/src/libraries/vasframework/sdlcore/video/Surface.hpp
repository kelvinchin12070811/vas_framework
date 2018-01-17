#pragma once
#include <SDL.h>
#include "../../VASConfig.hpp"
#include "../SDLComponentBase.hpp"

namespace sdl
{
	class VAS_DECLSPEC Surface : public SDLComponentBase<SDL_Surface>
	{
	public:
		Surface();
		explicit Surface(SDL_Surface* refInstance, SDLComponentBase::DeleterType deleter);
		Surface(const Surface& other);
		Surface(Surface&& other);
		~Surface();

		Surface operator=(const Surface& rhs);
		Surface operator=(Surface&& other);
		Surface& operator=(std::nullptr_t);
	
		static void defDeleter(SDL_Surface* instance);
		static void notDeleteDeleter(SDL_Surface* instance);
	};
}