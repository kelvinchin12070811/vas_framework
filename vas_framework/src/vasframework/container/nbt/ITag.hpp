#pragma once
#include "NBTSerializer.hpp"
#include "../../sreflex/Util.hpp"

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
		virtual void serialize(const std::string& name, NBTSerializer& serializer) = 0;
	};
}