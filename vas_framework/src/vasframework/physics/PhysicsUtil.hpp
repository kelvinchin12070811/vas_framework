//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include "../VASConfig.hpp"

#ifdef VAS_HAS_B2D
#include <Box2D/Box2D.h>
#include <boost/rational.hpp>
#include "../math/Vector2.hpp"

namespace vas::physics
{
	/**
	 * @ingroup physics
	 * @{
	 */
	/**
	 * @brief Utility that help to work on axises scalling.
	 * This utility provided functions that cast pixel based axises to real axises(meter).
	 * 
	 * @note The y axis will be flipped along the x axis (by multipling it to negative sign.
	 * @note The default scale of pixel based axises over real axises are 32:1 (32 pixel = 1 meter).
	 */
	class VAS_DECLSPEC CoordinateTools
	{ /** @} */
	public:
		/** Set axises scale factor. */
		static void setPixel2RealScale(boost::rational<int> scale);
		/** Get axises scale factor. */
		static const boost::rational<int>& getPixel2RealScale();

		/** Cast b2Vec2 to vas::Vector2. */
		static Vector2 realToPx(const b2Vec2& vec);
		/** Cast vas::Vector2 to b2Vec2. */
		static b2Vec2 pxToReal(const Vector2& vec);

		/** Cast pixel to meter. */
		static float pxToReal(float value);
		/** Cast meter to pixel. */
		static float realToPx(float value);
	private:
		static boost::rational<int> pixel2RealScale;
	};
}
#endif // VAS_HAS_B2D