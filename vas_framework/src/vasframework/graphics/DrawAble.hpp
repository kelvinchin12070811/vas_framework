#pragma once
#include "Camera.hpp"
#include "../sdlcore/video/Renderer.hpp"

namespace vas
{
	/** @addtogroup graphics
		  @{
	*/
	/** @brief The interface of all DrawAble object.
		  
		  | Header | Namespace |
		  | : --- : | : --- : |
		  | vasframework/graphics/DrawAble.hpp | vas |
	*/
	class DrawAble
	{/** @} */
	public:
		virtual ~DrawAble() {}

		/** Tick this DrawAble object. */
		virtual void tick() = 0;
		/** Draw this DrawAble object.
			  @param renderer Renderer use to draw this object, default renderer is used if nullptr.
			  @param camera Camera use to draw this object, default camera is used if nullptr.
		*/
		virtual void draw(sdl::Renderer* renderer = nullptr, Camera* camera = nullptr) = 0;
	};
}