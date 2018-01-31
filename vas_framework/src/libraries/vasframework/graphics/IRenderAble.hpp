#pragma once

namespace vas
{
	class IRendererAble
	{
	public:
		IRendererAble()
		{
		}

		virtual ~IRendererAble()
		{
		}

		virtual void tick() = 0;
		virtual void draw() = 0;
	};
}