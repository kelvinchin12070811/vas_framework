#pragma once
#include <SDL.h>
#include "../math/Vector2.hpp"

namespace vas
{
	class Camera
	{
	public:
		static Camera& getInstance();

		void targetOn(const Vector2& position);
		void setPosition(const Vector2& position);
		void move(const Vector2& position);

		void zoom(float scale);
		void resetZoom();

		const Vector2& getPosition();

		int getXOffset();
		int getYOffset();

		bool canSee(const SDL_Rect& destination);
	private:
		Camera();
		~Camera();
		SDL_Point constantWindowSize = { 0 };
		Vector2 position;
		SDL_Rect cameraRect = { 0 };
	};
	inline Camera& CameraAPI() { return Camera::getInstance(); };
}