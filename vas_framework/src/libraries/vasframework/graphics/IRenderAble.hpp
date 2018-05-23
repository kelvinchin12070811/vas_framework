#pragma once

namespace vas
{
	class IRenderAble
	{
	public:
		virtual ~IRenderAble() {}

		virtual void tick() = 0;
		virtual void draw() = 0;
	};
}