#include "MoveAble.hpp"

namespace vas
{
	MoveAble::MoveAble()
	{
	}

	MoveAble::MoveAble(const Vector2 & position):
		position(position)
	{
	}


	MoveAble::~MoveAble()
	{
	}

	void MoveAble::setPosition(const Vector2 & position)
	{
		if (this->position != position)
		{
			this->position = position;
		}
	}

	void MoveAble::move(const Vector2 & movement)
	{
		this->position += movement;
	}

	const Vector2 & MoveAble::getPosition() const
	{
		return position;
	}
}