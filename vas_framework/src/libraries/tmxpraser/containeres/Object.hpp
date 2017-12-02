#pragma once
#include <string>
#include <map>
#include "../../VASFramework/math/Vector2.hpp"
#include "../../VASFramework/math/Angle.hpp"
#include "../../VASFramework/containers/Properties.hpp"

namespace vas
{
	struct Object
	{
		size_t id;
		std::wstring name;
		std::wstring type;
		bool visible;
		Vector2 position;
		uint32_t width;
		uint32_t height;
		Angle rotation;
		Properties customProperties;
	};
}