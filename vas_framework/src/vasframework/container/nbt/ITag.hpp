#pragma once

namespace vas
{
	/** @addtogroup nbt_tag
		  @{
	*/
	/** @brief Basic interface that all NBT Tags type must inherited.
		  
		  ITag is the main interface that all NBT Tags instance must inherited.
	*/
	class ITag
	{ /** @} */
	public:
		ITag() {}
		virtual ~ITag() = 0 {}
	};
}