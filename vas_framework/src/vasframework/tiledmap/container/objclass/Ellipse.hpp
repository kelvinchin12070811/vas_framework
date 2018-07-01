#pragma once
#include "IShape.hpp"
#include "../../../math/Vector2.hpp"

namespace vas
{
	class Ellipse : public IShape
	{
	public:
		Vector2 position;
		int width{ 0 };
		int height{ 0 };
	};
}