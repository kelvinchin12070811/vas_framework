#pragma once
#include <memory>
#include <string>
#include "../../math/Vector2.hpp"
#include "../../container/PropertyList.hpp"
#include "objclass/IShape.hpp"

namespace vas
{
	struct ObjectData
	{
		std::string name;
		std::string type;
		std::unique_ptr<IShape> instance;
		PropertyList properties;
	};
}