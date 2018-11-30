#pragma once
#include <functional>

namespace vas
{
	/** @addtogroup animate
		  @{
	*/
	/** @brief The wraper of the numeric attribute of object.
	*/
	template <typename AttrType>
	struct AttrWrap
	{ /** @} */
		using WrappedType = AttrType;
		/** Create wrapper of setter
			  @param mutator Function pointer to the setter of object.
		*/
		AttrWrap(std::function<void(AttrType)> mutator) : mutator(mutator) {}
		/** Access the setter. */
		void operator()(double value)
		{
			mutator(static_cast<AttrType>(value));
		}
	protected:
		std::function<void(AttrType)> mutator;
	};
}