//===========================================================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//===========================================================================================================
#pragma once
#include "NBTSerializer.hpp"
#include "../../sreflex/Util.hpp"

namespace vas
{
	/**
	 * @ingroup nbt_tag
	 * @{
	 */
	/**
	 * @brief Basic interface that all NBT Tags type must inherited.
	 * 
	 * ITag is the main interface that all NBT Tags instance must inherited.
	 */
	class ITag
	{ /** @} */
	public:
		ITag() = default;
		virtual ~ITag() = 0;

		/**
		 * Serailize or deserialize the tag.
		 * @param[in] name Name of the tag.
		 * @param[in] serializer Serializer that use to serialize the tag.
		 */
		virtual void serialize(const std::string& name, NBTSerializer& serializer) = 0;
	};

	inline ITag::~ITag() = default;
}