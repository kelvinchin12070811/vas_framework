#include "SDLFunctionBridge.hpp"

namespace vas
{
	std::shared_ptr<SDL_Window> SDLFunctionBridge::newSDLWindow(SDL_Window * instance)
	{
		return std::shared_ptr<SDL_Window>(instance, SDL_DestroyWindow);
	}

	std::shared_ptr<SDL_Renderer> SDLFunctionBridge::newSDLRenderer(SDL_Renderer * instance)
	{
		return std::shared_ptr<SDL_Renderer>(instance, SDL_DestroyRenderer);
	}

	std::shared_ptr<SDL_Surface> SDLFunctionBridge::newSDLSurface(SDL_Surface * instance)
	{
		return std::shared_ptr<SDL_Surface>(instance, SDL_FreeSurface);
	}

	std::shared_ptr<SDL_Texture> SDLFunctionBridge::newSDLTexture(SDL_Texture * instance)
	{
		return std::shared_ptr<SDL_Texture>(instance, SDL_DestroyTexture);
	}

	std::shared_ptr<Mix_Music> SDLFunctionBridge::newMixMusic(Mix_Music * instance)
	{
		return std::shared_ptr<Mix_Music>(instance, Mix_FreeMusic);
	}

	std::shared_ptr<Mix_Chunk> SDLFunctionBridge::newMixChunk(Mix_Chunk * instance)
	{
		return std::shared_ptr<Mix_Chunk>(instance, Mix_FreeChunk);
	}

	std::shared_ptr<TTF_Font> SDLFunctionBridge::newTTFFont(TTF_Font * instance)
	{
		return std::shared_ptr<TTF_Font>(instance, TTF_CloseFont);
	}

	SDL_Point SDLFunctionBridge::newSDLPoint(int x, int y)
	{
		return { x, y };
	}

	SDL_Rect SDLFunctionBridge::newSDLRect(int x, int y, int w, int h)
	{
		return{ x, y, w, h };
	}

	inline namespace operator_plugins
	{
		inline namespace sdl_rect
		{
			SDL_Rect operator+(const SDL_Rect & lhs, const SDL_Rect & rhs)
			{
				SDL_Rect temp = lhs;
				temp.x += rhs.x;
				temp.y += rhs.y;
				temp.w += rhs.w;
				temp.h += rhs.h;
				return temp;
			}

			SDL_Rect operator-(const SDL_Rect & lhs, const SDL_Rect & rhs)
			{
				SDL_Rect temp = lhs;
				temp.x -= rhs.x;
				temp.y -= rhs.y;
				temp.w -= rhs.w;
				temp.h -= rhs.h;
				return temp;
			}

			SDL_Rect operator*(const SDL_Rect & lhs, const SDL_Rect & rhs)
			{
				SDL_Rect temp = lhs;
				temp.x *= rhs.x;
				temp.y *= rhs.y;
				temp.w *= rhs.w;
				temp.h *= rhs.h;
				return temp;
			}

			SDL_Rect operator/(const SDL_Rect & lhs, const SDL_Rect & rhs)
			{
				SDL_Rect temp = lhs;
				temp.x /= rhs.x;
				temp.y /= rhs.y;
				temp.w /= rhs.w;
				temp.h /= rhs.h;
				return temp;
			}

			const SDL_Rect& operator+=(SDL_Rect & lhs, const SDL_Rect & rhs)
			{
				lhs.x += rhs.x;
				lhs.y += rhs.y;
				lhs.w += rhs.w;
				lhs.h += rhs.h;
				return lhs;
			}

			const SDL_Rect & operator-=(SDL_Rect & lhs, const SDL_Rect & rhs)
			{
				lhs.x -= rhs.x;
				lhs.y -= rhs.y;
				lhs.w -= rhs.w;
				lhs.h -= rhs.h;
				return lhs;
			}

			const SDL_Rect & operator*=(SDL_Rect & lhs, const SDL_Rect & rhs)
			{
				lhs.x *= rhs.x;
				lhs.y *= rhs.y;
				lhs.w *= rhs.w;
				lhs.h *= rhs.h;
				return lhs;
			}

			const SDL_Rect & operator/=(SDL_Rect & lhs, const SDL_Rect & rhs)
			{
				lhs.x /= rhs.x;
				lhs.y /= rhs.y;
				lhs.w /= rhs.w;
				lhs.h /= rhs.h;
				return lhs;
			}
		}
		inline namespace sdl_point
		{
			SDL_Point operator+(const SDL_Point & lhs, const SDL_Point & rhs)
			{
				SDL_Point temp = lhs;
				temp.x += rhs.x;
				temp.y += rhs.y;
				return temp;
			}

			SDL_Point operator-(const SDL_Point & lhs, const SDL_Point & rhs)
			{
				SDL_Point temp = lhs;
				temp.x -= rhs.x;
				temp.y -= rhs.y;
				return temp;
			}

			SDL_Point operator*(const SDL_Point & lhs, const SDL_Point & rhs)
			{
				SDL_Point temp = lhs;
				temp.x *= rhs.x;
				temp.y *= rhs.y;
				return temp;
			}

			SDL_Point operator/(const SDL_Point & lhs, const SDL_Point & rhs)
			{
				SDL_Point temp = lhs;
				temp.x /= rhs.x;
				temp.y /= rhs.y;
				return temp;
			}

			const SDL_Point & operator+=(SDL_Point & lhs, const SDL_Point & rhs)
			{
				lhs.x += rhs.x;
				lhs.y += rhs.y;
				return lhs;
			}

			const SDL_Point & operator-=(SDL_Point & lhs, const SDL_Point & rhs)
			{
				lhs.x -= rhs.x;
				lhs.y -= rhs.y;
				return lhs;
			}
			
			const SDL_Point & operator*=(SDL_Point & lhs, const SDL_Point & rhs)
			{
				lhs.x *= rhs.x;
				lhs.y *= rhs.y;
				return lhs;
			}

			const SDL_Point & operator/=(SDL_Point & lhs, const SDL_Point & rhs)
			{
				lhs.x /= rhs.x;
				lhs.y /= rhs.y;
				return lhs;
			}
		}
	}
}