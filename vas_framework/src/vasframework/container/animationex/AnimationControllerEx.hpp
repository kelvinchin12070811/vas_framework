#pragma once
#include <chrono>
#include <memory>
#include <vector>
#include "Animateable.hpp"
#include "AutoControllable.hpp"
#include "../../VASConfig.hpp"

namespace vas
{
	class VAS_DECLSPEC AdvAnimController : public AutoControllable
	{
	public:
		AdvAnimController();
		~AdvAnimController();

		void tick() override;
		void restart();

		const Animateable* currentAnim() const;
		size_t currentAnimIndex() const;

	public: //accessors
		bool isFinished() const;
		bool isLoopingAnim() const;

	public: //mutators
		void setLoopingAnim(bool value);

	private:
		bool finished{ false };
		bool loopAnim{ false };
		std::vector<std::unique_ptr<Animateable>> animationList;
		std::vector<std::unique_ptr<Animateable>>::const_iterator curAnim;
	};
}