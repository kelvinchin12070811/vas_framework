#pragma once
#include <SDL.h>
#include "../../VASConfig.hpp"
#include "../SDLComponentBase.hpp"
#include "../Math.hpp"

namespace sdl
{
	class VAS_DECLSPEC Surface : public SDLComponentBase<SDL_Surface>
	{
	public:
		Surface();
		explicit Surface(SDL_Surface* refInstance, SDLComponentBase::DeleterType deleter = &Surface::notDeleteDeleter);
		Surface(uint32_t flags, const Point& size, int depth, uint32_t rMask, uint32_t gMask, uint32_t bMask, uint32_t aMask);
		//Surface(uint32_t flags, const Point& size, int depth, uint32_t format);
		Surface(void* pixels, const Point& size, int depth, int pitch, uint32_t rMask, uint32_t gMask, uint32_t bMask, uint32_t aMask);
		//Surface(void* pixels, const Point& size, int depth, int pitch, uint32_t format);

		bool lock();
		void loadBMP(std::string file);
		void loadBMPRw(SDL_RWops* src, bool freeSrc = true);

		bool saveBMP(std::string file);
		bool saveBMPRw(SDL_RWops* dest, bool freeSrc = true);
		bool setPalette(SDL_Palette* palette);
		bool setRLE(int flags);

		void unlock();

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