//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "PhysicsUtil.hpp"

#ifdef VAS_HAS_B2D
namespace vas::physics
{
	boost::rational<int> CoordinateTools::pixel2RealScale{ 32, 1 };
	
	void CoordinateTools::setPixel2RealScale(boost::rational<int> scale)
	{
		pixel2RealScale = scale;
	}
	
	const boost::rational<int>& CoordinateTools::getPixel2RealScale()
	{
		return pixel2RealScale;
	}

	Vector2 CoordinateTools::realToPx(const b2Vec2 & vec)
	{
		auto scale = boost::rational_cast<float>(pixel2RealScale);
		return { vec.x * scale, -(vec.y * scale) };
	}

	b2Vec2 CoordinateTools::pxToReal(const Vector2 & vec)
	{
		auto result = vec / boost::rational_cast<float>(pixel2RealScale);
		return b2Vec2{ result.x, -result.y };
	}
	
	float CoordinateTools::pxToReal(float value)
	{
		return value / boost::rational_cast<float>(pixel2RealScale);
	}
	
	float CoordinateTools::realToPx(float value)
	{
		return value * boost::rational_cast<float>(pixel2RealScale);
	}
}
#endif // VAS_HAS_B2D