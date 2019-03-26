//===========================================================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//===========================================================================================================
#pragma once
#include <boost/assert.hpp>
#include <functional>
#include <string>

namespace vas
{
	/**
	 * @ingroup nbt_tag
	 * @{
	 */
	/**
	 * @brief The interface of all serializer and deserializer.
	 * 
	 * The NBTSerializer is the object that all nbt tags take to serialize or deserialize their data. The
	 * serializer have
	 * several member functions to accept value from the nbt tree. Specialization on ValueWrapperTag::serialize
	 * needed for other type.
	 */
	class NBTSerializer
	{ /** @} */
	public:
		using ArraySizeSetter = std::function<void(size_t)>; /**< Function object to resize the target array container. */
	public:
		NBTSerializer() = default;
		NBTSerializer(const NBTSerializer&) = default;
		NBTSerializer(NBTSerializer&&) noexcept = default;
		NBTSerializer& operator=(const NBTSerializer&) = default;
		NBTSerializer& operator=(NBTSerializer&&) noexcept = default;
		virtual ~NBTSerializer() = 0;
		/**
		 * Begin tree structure.
		 * @param[in] name Name of the tree.
		 */
		virtual void treeStart(const std::string& name) = 0;
		virtual void treeEnd() = 0; /**< End of the tree. */
		/**
		 * Begin of an array structure.
		 * @param[in] name Name of the array.
		 */
		virtual void arrayStart(const std::string& name) = 0;
		virtual void arrayEnd() = 0; /**< End of an array structure. */
		/**
		 * Resize the target array container if possible.
		 * @param[in] setter Function pointer to resize the target array container, Won't do any thing if
		 * nullptr.
		 */
		virtual void arraySizeSetter(ArraySizeSetter setter) = 0;

		virtual void accept(const std::string& name, std::byte& value) = 0; /**< Accept std::byte. */
		virtual void accept(const std::string& name, std::int16_t& value) = 0; /**< Accept std::int16_t. */
		virtual void accept(const std::string& name, std::int32_t& value) = 0; /**< Accept std::int32_t. */
		virtual void accept(const std::string& name, std::uint32_t& value) = 0; /**< Accept std::uint32_t. */
		virtual void accept(const std::string& name, std::int64_t& value) = 0; /**< Accept std::int64_t. */
		virtual void accept(const std::string& name, std::uint64_t& value) = 0; /**< Accept std::uint64_t. */
		virtual void accept(const std::string& name, float& value) = 0; /**< Accept float. */
		virtual void accept(const std::string& name, double& value) = 0; /**< Accept double. */
		virtual void accept(const std::string& name, bool& value) = 0; /**< Accept bool. */
		virtual void accept(const std::string& name, std::string& value) = 0; /**< Accept std::string. */
	};

	inline NBTSerializer::~NBTSerializer() = default;
}