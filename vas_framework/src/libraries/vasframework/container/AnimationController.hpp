#pragma once
#include <chrono>
#include "../VASConfig.hpp"
#include "../math/Counter.hpp"
#include "AnimationStrip.hpp"

namespace vas
{
	class VAS_DECLSPEC AnimationController
	{
	public:
		AnimationController();
		AnimationController(const AnimationStrip& frames, std::chrono::milliseconds updateDelay);
		~AnimationController();

		void load(const AnimationStrip& frames, std::chrono::milliseconds updateDelay);
		void tick();

	public: //getters
		AnimationStrip::value_type getCurrentFrame();
		size_t getCurrentFrameIndex();

	private:
		AnimationStrip frames;
		Counter frameIndexer;
		Counter frameUpdateTimer;
	};
}