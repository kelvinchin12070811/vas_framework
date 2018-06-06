#pragma once
#include <vector>
#include "NBTCompoundTag.hpp"
#include "../../math/Vector2.hpp"

namespace vas
{
	template <typename ValueType>
	class ValueWarpperTag : public ITag
	{
	public:
		ValueWarpperTag(const ValueType& value): value(value)
		{
		}

		ValueWarpperTag(ValueType&& value): value(std::move(value))
		{
		}

		operator ValueType&()
		{
			return value;
		}
	private:
		ValueType value;
	};

	using ByteTag = ValueWarpperTag<uint8_t>;
	using Int16Tag = ValueWarpperTag<int16_t>;
	using Int32Tag = ValueWarpperTag<int32_t>;
	using UInt32Tag = ValueWarpperTag<uint32_t>;
	using Int64Tag = ValueWarpperTag<int64_t>;
	using FloatTag = ValueWarpperTag<float>;
	using DoubleTag = ValueWarpperTag<double>;
	using BooleanTag = ValueWarpperTag<bool>;
	using StringTag = ValueWarpperTag<std::string>;

	template <typename T>
	using ArrayTag = ValueWarpperTag<std::vector<T>>;

	using Vector2Tag = ValueWarpperTag<Vector2>;
}