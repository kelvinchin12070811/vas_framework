#pragma once

namespace vas
{
	class AutoControllable
	{
		virtual void tick() = 0;
		virtual ~AutoControllable() = 0;
	};
}