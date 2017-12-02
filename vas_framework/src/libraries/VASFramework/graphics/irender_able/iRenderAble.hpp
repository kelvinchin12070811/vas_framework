#pragma once

namespace vas
{
	class iRenderAble
	{
	public:
		iRenderAble() {}
		virtual ~iRenderAble() {}

		virtual void tick() = 0;
		virtual void draw() = 0;
	};
}