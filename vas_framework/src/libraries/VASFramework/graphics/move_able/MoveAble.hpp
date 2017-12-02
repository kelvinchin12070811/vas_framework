#pragma once
#include <SDL.h>
#include "../../math/Vector2.hpp"

namespace vas
{
	class MoveAble
	{
	public:
		MoveAble();
		MoveAble(const Vector2& position);
		~MoveAble();

		void setPosition(const Vector2& position);
		void move(const Vector2& movement);

		const Vector2& getPosition() const;
	protected:
		Vector2 position;
	};
}