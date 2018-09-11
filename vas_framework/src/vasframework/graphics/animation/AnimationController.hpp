#pragma once
#include <chrono>
#include "AutoControllable.hpp"
#include "../../VASConfig.hpp"
#include "../../math/Counter.hpp"
#include "AnimationStrip.hpp"

namespace vas
{
	class VAS_DECLSPEC AnimationController : public AutoControllable
	{
	public:
		AnimationController();
		AnimationController(const AnimationStrip& frames, std::chrono::milliseconds updateDelay);
		~AnimationController();

		void load(const AnimationStrip& frames, std::chrono::milliseconds updateDelay);
		void tick() override;

		void reset();

	public: //getters
		AnimationStrip::value_type getCurrentFrame();
		size_t getCurrentFrameIndex();

	private:
		AnimationStrip frames;
		Counter frameIndexer;
		Counter frameUpdateTimer;
	};
}