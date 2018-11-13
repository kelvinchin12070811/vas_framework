#include "AnimateAble.hpp"

namespace vas
{
	bool AnimateAble::done() const
	{
		return finished;
	}

	void AnimateAble::reset()
	{
		finished = true;
	}
}