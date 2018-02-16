#pragma once

namespace vas
{
	class IRendererAble
	{
	public:
		virtual ~IRendererAble() {}

		virtual void tick() = 0;
		virtual void draw() = 0;
	};
}