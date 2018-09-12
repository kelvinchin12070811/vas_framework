#pragma once

namespace vas
{
	struct AutoControllable
	{
		virtual void tick() = 0;
	};
}