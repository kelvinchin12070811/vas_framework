#pragma once

namespace vas
{
	class AutoControllable
	{
	public:
		virtual void tick() = 0 {}
		virtual ~AutoControllable() = 0 {}
	};
}