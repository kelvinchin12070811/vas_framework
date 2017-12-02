#pragma once
#include <vector>
#include "../../VASFramework/math/Clock.hpp"
#include "../../VASFramework/math/Timer.hpp"

namespace vas
{
	class TileAnimation
	{
	public:
		TileAnimation();
		TileAnimation(const std::vector<uint32_t>& frameDurations, const std::vector<uint32_t>& frames);
		TileAnimation(std::vector<uint32_t>&& frameDurations, std::vector<uint32_t>&& frames);
		TileAnimation(const TileAnimation&) = delete;
		TileAnimation(TileAnimation&& rhs) noexcept;
		~TileAnimation();

		void tick();
		uint32_t getCurrentFrameIndex();
		uint32_t getCurrentFrame();
		uint32_t getTileId();

		std::vector<uint32_t> frameDurations;
		std::vector<uint32_t> frames;
		Clock updateClock;
		Counter frameCounter;
	};
}