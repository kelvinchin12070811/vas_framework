#pragma once

namespace vas
{
	class AnimateAble
	{
	public:
		virtual void tick() = 0 {}
		virtual bool done() const = 0 {}
		virtual ~AnimateAble() = 0 {}
	};
}