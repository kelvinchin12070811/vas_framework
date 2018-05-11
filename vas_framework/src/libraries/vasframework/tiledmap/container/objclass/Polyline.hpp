#pragma once
#include <vector>
#include "IShape.hpp"
#include "../../../math/Vector2.hpp"

namespace vas
{
	class Polyline : public IShape
	{
	public:
		Vector2 position;
		std::vector<Vector2> line;
	};
}