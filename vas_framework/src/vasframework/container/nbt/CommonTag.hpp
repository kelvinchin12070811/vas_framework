#pragma once
#include <vector>
#include "NBTCompoundTag.hpp"
#include "../../math/Vector2.hpp"
/** @addtogroup container
	  @{
*/
/** @defgroup nbt_tag NBT Tag
	  @brief The NBT Tag system implementation.

	  The NBT(Named Binary Tag) structure is a tree like data structure with multiple data entrys. The idea is originaly from
	  the game "Minecraft".

	  The NBT Tag library in vas_framework is vas_framework's implementation of NBT structure in C++.
*/
/** @} */
namespace vas
{
	/** @addtogroup nbt_tag
		  @{
	*/
	/** @brief A template class to define a custom data type to work with NBT.
		  
		  The ValueWrapperTag is a template class that help user to define their class to work with NBT Tag structure. The
		  wrapper is designed to emulate normal data types function with operator overloading, it is safe to assign other
		  value with same type to it.

		  @tparam ValueType Data type to wrap.
	*/
	template <typename ValueType>
	class ValueWarpperTag : public ITag
	{ /** @} */
	public:
		using TagType = ValueType; /**< Type of the wrapper emulated. */
		/** @memberof ValueWrapperTag
			  Copy constructor.
		*/
		ValueWarpperTag(const ValueType& value): value(value)
		{
		}

		/** @memberof ValueWrapperTag
			  Move constructor.
		*/
		ValueWarpperTag(ValueType&& value): value(std::move(value))
		{
		}

		/** @memberof ValueWrapperTag
			  Convert wrapper to reference of ValueType.
		*/
		operator ValueType&()
		{
			return value;
		}

		/** @memberof ValueWrapperTag
			  Convert wrapper to const reference of ValueType.
		*/
		operator const ValueType&() const
		{
			return value;
		}
	private:
		ValueType value;
	};

	/** @name Predefined tag
		  
		  The predefined tag that use with NBT structure. #include <vasframework/container/nbt/CommonTag.hpp> to use them.
		  @{
	*/
	using ByteTag = ValueWarpperTag<uint8_t>; /**< Byte tag. */
	using Int16Tag = ValueWarpperTag<int16_t>; /**< Singed 16 bit int tag. */
	using Int32Tag = ValueWarpperTag<int32_t>; /**< Singed 32 bit int tag. */
	using UInt32Tag = ValueWarpperTag<uint32_t>; /**< Unsinged 32 bit int tag. */
	using Int64Tag = ValueWarpperTag<int64_t>; /**< Singed 64 bit int tag. */
	using FloatTag = ValueWarpperTag<float>; /**< Float tag. */
	using DoubleTag = ValueWarpperTag<double>; /**< Double tag. */
	using BooleanTag = ValueWarpperTag<bool>; /**< Boolean tag. */
	using StringTag = ValueWarpperTag<std::string>; /**< String tag. */

	/** Array of data tag. */
	template <typename T>
	using ArrayTag = ValueWarpperTag<std::vector<T>>;

	using Vector2Tag = ValueWarpperTag<Vector2>; /**< vas::Vector2 tag. */

	/** @} */
}