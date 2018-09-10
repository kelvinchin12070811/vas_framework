#pragma once
#include "../VASConfig.hpp"
#include "../math/Vector2.hpp"
#include "../sdlcore/Math.hpp"

namespace vas
{
	/** @addtogroup graphics
		  @{
	*/
	/** @brief Camera that spot all of the elements in the game's world and tell which elements to render to Renderer.

		  | Header | Namespace |
		  | : --- : | : --- : |
		  | vasframework/graphics/Camera.hpp | vas |

		  Camera is an object that tell the Renderer what is going to be rendered on the canvas and where it will be. The
		  Camera also tell the Renderer how to render the objects like its' size.

		  A camera is a non-copyable and not-moveable class. This property use to ensure a camera instance will not be
		  mutated some how in the code.

		  Camera will state each object is weather static on camera or not. If an object is static on camera, the object will
		  not bee affected by the movement of camera.
	*/
	class VAS_DECLSPEC Camera
	{ /** @} */
	public:
		/** Get the main instance of the camera use by the framework

			  @warning This function has been depercated scene it have been moved under Base::camera attribute. This function
			  is keep for backward compability issues. Use Base::getCamera() instead.

			  @return Main instance of the camera
		*/
		static Camera& getInstance();

		/** Check if the object is visible on the camera.
			  @param other The object's rect that need to be spoted.
			  @retval true if the object is visible.
		*/
		bool canSee(const sdl::Rect& other);
		/** Check if the object is visible on the camera.
			  @param other  The object's position that need to be spoted.
			  @param size Size of the object.

			  @retval true if the object is visible.
		*/
		bool canSee(const Vector2& other, const sdl::Point& size);

		/** Get the position of a object about where it will be located on the camera.
			  @param position The position of the object.
			  @param staticOnCamera State if the object is static on camera.

			  @return position of the object on the camera canvas.
		*/
		Vector2 getPosOnCamera(const Vector2 & position, bool staticOnCamera = false);
		/** Get the position of a object about where it will be located on the camera.
			  @param rect The rect of the object.
			  @param staticOnCamera State if the object is static on camera.
			  
			  @return position of the object on the camera canvas.
		*/
		sdl::Rect getRectOnCamera(const sdl::Rect& rect, bool staticOnCamera = false);

		/** Move the position of camera
			  @param movement The motion vector of the camera.
		*/
		void move(const Vector2& movement);
		/** Let camera focus on certain object's position.
			  @param position The position of the object need to be focus.

			  @note This function will not focus on the exact center of the object, top left corner instead. Make your own
			  adjustment to fit your object.
		*/
		void focusOn(const Vector2& position);
		/** Zoom in or out on the camera, using simple multipication calculation.
			  @param value Amout of factor that need to zoom in, larger then 1 for larger, in between 0 - 1 for smaller.
		*/
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

		Camera(const Camera&) = delete;
		Camera(Camera&&) = delete;
		Camera& operator=(const Camera&) = delete;
		Camera& operator=(Camera&&) = delete;
	private:
		/** Position of the camera.
			  - __mutators__
				  -# void setPosition(const Vector2& value)

			  - __accessors__
					-# Vector2 getPosition()
		*/
		Vector2 position;
		/** Canvas size for the camera to spot.
			  - __mutators__
					-# void setSize(const sdl::Point& value)
			  - __accessors__
					-# sdl::Point getSize()
		*/
		sdl::Point size;
		/** Multiplyer of the camera rect. This attribute state how large the object will been draw on the canvas
			  - __mutators__
					-# void setSize(double value)
			  - __accessors__
					-# double getSize()
		*/
		double multiplyer{ 1.0 };
	};
}