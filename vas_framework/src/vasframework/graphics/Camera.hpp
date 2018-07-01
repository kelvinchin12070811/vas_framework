#pragma once
#include "../VASConfig.hpp"
#include "../math/Vector2.hpp"
#include "../sdlcore/Math.hpp"

namespace vas
{
	class VAS_DECLSPEC Camera
	{
	public:
		static Camera& getInstance();

		bool canSee(const sdl::Rect& other);
		bool canSee(const Vector2& other, const sdl::Point& size);

		Vector2 getPosOnCamera(const Vector2 & position, bool staticOnCamera = false);
		sdl::Rect getRectOnCamera(const sdl::Rect& rect, bool staticOnCamera = false);

		void move(const Vector2& movement);
		void focusOn(const Vector2& position);
		void zoom(double value);

	public: //setters
		void setPosition(const Vector2& value);
		void setSize(const sdl::Point& value);
		void setMultiplyer(double value);

	public: //getters
		Vector2 getPosition();
		sdl::Point getSize();
		double getMultiplyer();

		Camera();
		~Camera();
	private:
		Vector2 position;
		sdl::Point size;
		double multiplyer{ 1.0 };
	};
}