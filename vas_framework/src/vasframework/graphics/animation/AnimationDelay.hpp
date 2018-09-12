#pragma once
#include <chrono>
#include "AnimateAble.hpp"
#include "../../VASConfig.hpp"

namespace vas
{
	class VAS_DECLSPEC AnimationDelay : public AnimateAble
	{
	public:
		AnimationDelay();
		explicit AnimationDelay(std::chrono::nanoseconds duration);
		~AnimationDelay();

		void tick() override;
		bool done() const override;

	public: //mutators
		void setDuration(std::chrono::nanoseconds value);
		
	public: //accessors
		std::chrono::nanoseconds getDuration() const;
	private:
		bool finished{ false };
		std::chrono::nanoseconds duration;
		std::chrono::steady_clock::time_point startTime;
	};
}