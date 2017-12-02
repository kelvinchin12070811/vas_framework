#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <memory>

namespace vas
{
	class SDLFunctionBridge
	{
	public:
		static std::shared_ptr<SDL_Window> newSDLWindow(SDL_Window* instance);
		static std::shared_ptr<SDL_Renderer> newSDLRenderer(SDL_Renderer* instance);
		static std::shared_ptr<SDL_Surface> newSDLSurface(SDL_Surface* instance);
		static std::shared_ptr<SDL_Texture> newSDLTexture(SDL_Texture* instance);

		static std::shared_ptr<Mix_Music> newMixMusic(Mix_Music* instance);
		static std::shared_ptr<Mix_Chunk> newMixChunk(Mix_Chunk* instance);

		static std::shared_ptr<TTF_Font> newTTFFont(TTF_Font* instance);

		static SDL_Point newSDLPoint(int x, int y);

		static SDL_Rect newSDLRect(int x, int y, int w = 0, int h = 0);
	};

	inline namespace operator_plugins
	{
		inline namespace sdl_rect
		{
			SDL_Rect operator+(const SDL_Rect& lhs, const SDL_Rect& rhs);
			SDL_Rect operator-(const SDL_Rect& lhs, const SDL_Rect& rhs);
			SDL_Rect operator*(const SDL_Rect& lhs, const SDL_Rect& rhs);
			SDL_Rect operator/(const SDL_Rect& lhs, const SDL_Rect& rhs);

			const SDL_Rect& operator+=(SDL_Rect& lhs, const SDL_Rect& rhs);
			const SDL_Rect& operator-=(SDL_Rect& lhs, const SDL_Rect& rhs);
			const SDL_Rect& operator*=(SDL_Rect& lhs, const SDL_Rect& rhs);
			const SDL_Rect& operator/=(SDL_Rect& lhs, const SDL_Rect& rhs);
		}

		inline namespace sdl_point
		{
			SDL_Point operator+(const SDL_Point& lhs, const SDL_Point& rhs);
			SDL_Point operator-(const SDL_Point& lhs, const SDL_Point& rhs);
			SDL_Point operator*(const SDL_Point& lhs, const SDL_Point& rhs);
			SDL_Point operator/(const SDL_Point& lhs, const SDL_Point& rhs);

			const SDL_Point& operator+=(SDL_Point& lhs, const SDL_Point& rhs);
			const SDL_Point& operator-=(SDL_Point& lhs, const SDL_Point& rhs);
			const SDL_Point& operator*=(SDL_Point& lhs, const SDL_Point& rhs);
			const SDL_Point& operator/=(SDL_Point& lhs, const SDL_Point& rhs);
		}
	}
}