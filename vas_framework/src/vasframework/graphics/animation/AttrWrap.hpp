#pragma once
#include <functional>

namespace vas
{
	template <typename AttrType>
	struct AttrWrap
	{
		using WrappedType = AttrType;
		AttrWrap(std::function<void(AttrType)> mutator) : mutator(mutator) {}
		void operator()(double value)
		{
			mutator(static_cast<AttrType>(value));
		}
	protected:
		std::function<void(AttrType)> mutator;
	};
}