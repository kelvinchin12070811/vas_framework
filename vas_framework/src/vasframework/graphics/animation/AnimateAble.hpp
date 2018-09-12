#pragma once

namespace vas
{
	struct AnimateAble
	{
		virtual void tick() = 0;
		virtual bool done() const = 0;
	};
}