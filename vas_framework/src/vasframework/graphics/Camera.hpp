//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include "../VASConfig.hpp"
#include "../math/Vector2.hpp"
#include "../sdlcore/Math.hpp"

namespace vas
{
	/**
	 * @ingroup graphics
	 * @{
	 */
	/**
	 * @brief Camera that spot all of the elements in the game's world and tell which elements to render to Renderer.
	 * 
	 * Camera is an object that tell the Renderer what is going to be rendered on the canvas and where it will be. The
	 * Camera also tell the Renderer how to render the objects like its' size.
	 * 
	 * A camera is a non-copyable and not-moveable class. This property use to ensure a camera instance will not be
	 * mutated some how in the code.
	 * 
	 * Camera will state each object is weather static on camera or not. If an object is static on camera, the object will
	 * not bee affected by the movement of camera.
	 */
	class VAS_DECLSPEC Camera
	{ /** @} */
	public:
		/**
		 * Get the main instance of the camera use by the framework
		 * 
		 * @deprecated This function has been moved under Base::camera attribute and it is only keep
		 * for backward compability issues. Use Base::getCamera() instead.
		 * 
		 * @return Main instance of the camera
		 */
		static Camera& getInstance();

		/**
		 * Check if the object is visible on the camera.
		 * @param[in] other The object's rect that need to be spoted.
		 * @retval true if the object is visible.
		 */
		bool canSee(const sdl::Rect& other);
		/**
		 * Check if the object is visible on the camera.
		 * @param[in] other  The object's position that need to be spoted.
		 * @param[in] size Size of the object.
		 * 
		 * @retval true if the object is visible.
		 */
		bool canSee(const Vector2& other, const sdl::Point& size);

		/**
		 * Get the position of a object about where it will be located on the camera.
		 * @param[in] position The position of the object.
		 * @param[in] staticOnCamera State if the object is static on camera.
		 * 
		 * @return position of the object on the camera canvas.
		 */
		Vector2 getPosOnCamera(const Vector2 & position, bool staticOnCamera = false);
		/**
		 * Get the position of a object about where it will be located on the camera.
		 * @param[in] rect The rect of the object.
		 * @param[in] staticOnCamera State if the object is static on camera.
		 * 
		 * @return position of the object on the camera canvas.
		 */
		sdl::Rect getRectOnCamera(const sdl::Rect& rect, bool staticOnCamera = false);

		/**
		 * Move the position of camera
		 * @param[in] movement The motion vector of the camera.
		 */
		void move(const Vector2& movement);
		/**
		 * Move the position of camera with a boundary.
		 * @param[in] movement The motion vector of the camera.
		 * @param[in] min Minimum position of the camera.
		 * @param[in] max Maximum position of the camera.
		 */
		void move(const Vector2& movement, const Vector2& min, const Vector2& max);
		/**
		 * Let camera focus on certain object's position.
		 * @param[in] position The position of the object need to be focus.
		 * 
		 * @note This function will not focus on the exact center of the object, top left corner instead. Make your own
		 * adjustment to fit your object.
		 */
		void focusOn(const Vector2& position);
		/**
		 * Let camera focus on certain object's position in a boundary.
		 * @param[in] position The position of the object need to be focus.
		 * @param[in] min Minimum position of the camera.
		 * @param[in] max Maximum position of the camera.
		 * @note This function will not focus on the exact center of the object, top left corner instead. Make your own
		 * adjustment to fit your object.
		 */
		void focusOn(const Vector2& position, const Vector2& min, const Vector2& max);
		/**
		 * Zoom in or out on the camera, using simple multipication calculation.
		 * @param[in] value Amout of factor that need to zoom in, larger then 1 for larger, in between 0 - 1 for smaller.
		 */
		void zoom(double value);

	public: //setters
		void setPosition(const Vector2& value);
		void setSize(const sdl::Point& value);
		void setMultiplier(double value);

	public: //getters
		Vector2 getPosition();
		sdl::Point getSize();
		double getMultiplier();

		Camera() = default;
		~Camera() = default;

		Camera(const Camera&) = delete;
		Camera(Camera&&) = delete;
		Camera& operator=(const Camera&) = delete;
		Camera& operator=(Camera&&) = delete;
	private:
		/**
		 * Position of the camera.
		 * ####Mutators
		 * -# void setPosition(const Vector2& value)
		 * 
		 * ####Accessors
		 * -# Vector2 getPosition()
		 */
		Vector2 position;
		/**
		 * Canvas size for the camera to spot.
		 * ####Mutators
		 * -# void setSize(const sdl::Point& value)
		 * 
		 * ####Accessors
		 * -# sdl::Point getSize()
		 */
		sdl::Point size;
		/**
		 * Multiplier of the camera rect. This attribute state how large the object will been draw on the canvas
		 * ####Mutators
		 * -# void setMultiplier(double value)
		 * 
		 * ####Accessors
		 * -# double getMultiplier()
		 */
		double multiplier{ 1.0 };
	};
}