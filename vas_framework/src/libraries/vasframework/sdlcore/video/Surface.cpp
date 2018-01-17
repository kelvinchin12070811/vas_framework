#include "Surface.hpp"

namespace sdl
{
	Surface::Surface()
	{
	}

	Surface::Surface(SDL_Surface * refInstance, SDLComponentBase::DeleterType deleter) :
		SDLComponentBase(refInstance, deleter)
	{
	}

	Surface::Surface(const Surface & other):
		SDLComponentBase(other)
	{
	}

	Surface::Surface(Surface && other):
		SDLComponentBase(std::move(other.componentInstance))
	{
	}

	Surface::~Surface()
	{
	}

	Surface Surface::operator=(const Surface & rhs)
	{
		this->componentInstance = rhs.componentInstance;
		return *this;
	}

	Surface Surface::operator=(Surface && other)
	{
		this->componentInstance = std::move(other.componentInstance);
		return *this;
	}

	Surface & Surface::operator=(std::nullptr_t)
	{
		this->componentInstance = nullptr;
		return *this;
	}

	void Surface::defDeleter(SDL_Surface * instance)
	{
		SDL_FreeSurface(instance);
	}

	void Surface::notDeleteDeleter(SDL_Surface * instance)
	{
		return;
	}
}