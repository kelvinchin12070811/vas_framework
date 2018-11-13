#pragma once
#include <memory>
#include "../AnimateAble.hpp"

namespace vas
{
	struct State
	{
		std::unique_ptr<AnimateAble> animation;
	};
}