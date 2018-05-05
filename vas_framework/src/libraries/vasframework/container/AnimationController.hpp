#pragma once
#include "../VASConfig.hpp"
#include "../math/Counter.hpp"
#include "AnimationStrip.hpp"

namespace vas
{
	class VAS_DECLSPEC AnimationController
	{
	public:
		AnimationController();
		~AnimationController();
	private:
		AnimationStrip frameIndex;
		Counter frameCounter;
	};
}