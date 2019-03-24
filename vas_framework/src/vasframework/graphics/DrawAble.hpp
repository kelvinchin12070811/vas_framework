//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include "Camera.hpp"
#include "../sdlcore/video/Renderer.hpp"

namespace vas
{
	/**
	 * @ingroup graphics
	 * @{
	 */
	/**
	 * @brief The interface of all DrawAble object.
	 */
	class DrawAble
	{/** @} */
	public:
		virtual ~DrawAble() = 0;

		/** Tick this DrawAble object. */
		virtual void tick() = 0;
		/**
		 * Draw this DrawAble object.
		 * @param[in] renderer Renderer use to draw this object, default renderer is used if nullptr.
		 * @param[in] camera Camera use to draw this object, default camera is used if nullptr.
		 */
		virtual void draw(sdl::Renderer* renderer = nullptr, Camera* camera = nullptr) = 0;
	};

	inline DrawAble::~DrawAble() = default;
}