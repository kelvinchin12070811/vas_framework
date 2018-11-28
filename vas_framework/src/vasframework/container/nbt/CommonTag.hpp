#pragma once
#include <algorithm>
#include <boost/lexical_cast.hpp>
#include <iterator>
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
		ValueWarpperTag() : value(ValueType()) {}

		ValueWarpperTag(const ValueType& value): value(value)
		{
		}

		/** @memberof ValueWrapperTag
			  Move constructor.
		*/
		ValueWarpperTag(ValueType&& value): value(std::move(value))
		{
		}

		static std::unique_ptr<ValueWarpperTag> create()
		{
			return std::make_unique<ValueWarpperTag>();
		}

		static std::unique_ptr<ValueWarpperTag> create(ValueType value)
		{
			return std::make_unique<ValueWarpperTag>(std::move(value));
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

		ValueType& get()
		{
			return const_cast<ValueType&>(const_cast<const ValueWarpperTag*>(this)->get());
		}
		
		const ValueType& get() const
		{
			return value;
		}

		void serialize(const std::string& name, NBTSerializer& serializer) override
		{
			static_assert(std::numeric_limits<int>::is_specialized, "Non numeric data type must specialize member function ValueWarpperTag::serialize");
			serializer.accept(name, value);
		}
	private:
		ValueType value;
	};

	template <class T>
	class ArrayTag : public ITag, public std::vector<T>
	{
	public:
		ArrayTag() = default;
		~ArrayTag() = default;
		explicit ArrayTag(size_t size) : std::vector(size)
		{
		}

		template <class Iterator>
		ArrayTag(Iterator begin, Iterator end)
		{
			this->reserve(std::distance(begin, end));
			std::copy(begin, end, std::back_inserter(*this));
		}

		ArrayTag(std::initializer_list<T> list)
		{
			if (!this->empty()) this->clear();
			this->reserve(list.size());
			std::copy(list.begin(), list.end(), std::back_inserter(*this));
		}

		ArrayTag(const ArrayTag& rhs) : std::vector(rhs.begin(), rhs.end())
		{
		}

		ArrayTag(ArrayTag&& rhs) noexcept : std::vector(std::make_move_iterator(rhs.begin()), std::make_move_iterator(rhs.end))
		{
		}

		static std::shared_ptr<ArrayTag> create()
		{
			return std::make_unique<ArrayTag>();
		}

		static std::unique_ptr<ArrayTag> create(std::initializer_list<T> list)
		{
			return std::make_unique<ArrayTag>(std::move(list));
		}

		void serialize(const std::string& name, NBTSerializer& serializer) override
		{
			serializer.arrayStart(name);
			serializer.arraySizeSetter([this](size_t size) { this->resize(size); });
			for (size_t itr = 0; itr != this->size(); itr++)
				serializer.accept(boost::lexical_cast<std::string>(itr), this->at(itr));
			serializer.arrayEnd();
		}

		ArrayTag& operator=(const ArrayTag& rhs)
		{
			this->clear();
			this->reserve(rhs.size());
			std::copy(rhs.begin(), rhs.end(), std::back_inserter(this->begin()));
			return *this;
		}

		ArrayTag& operator=(ArrayTag&& rhs) noexcept
		{
			this->clear();
			this->reserve(rhs.size());
			for (auto& itr : rhs)
				this->push_back(std::move(itr));
			rhs.clear();
			return *this;
		}

		void swap(ArrayTag& other) noexcept
		{
			std::swap_ranges(other.begin(), other.end(), this->begin(), this->end());
		}
	};

	template<>
	void ArrayTag<std::shared_ptr<ITag>>::serialize(const std::string& name, NBTSerializer& serializer)
	{
		serializer.arrayStart(name);
		serializer.arraySizeSetter([this](size_t size) { this->resize(size); });
		for (size_t itr = 0; itr != this->size(); itr++)
			this->at(itr)->serialize(boost::lexical_cast<std::string>(itr), serializer);
		serializer.arrayEnd();
	}

	template <>
	void ValueWarpperTag<std::string>::serialize(const std::string& name, NBTSerializer& serializer)
	{
		serializer.accept(name, value);
	}

	template <>
	void ValueWarpperTag<vas::Vector2>::serialize(const std::string& name, NBTSerializer& serializer)
	{
		serializer.arrayStart(name);
		serializer.accept("0", value.x);
		serializer.accept("1", value.y);
		serializer.arrayEnd();
	}

	/** @name Predefined tag
		  
		  The predefined tag that use with NBT structure. #include <vasframework/container/nbt/CommonTag.hpp> to use them.
		  @{
	*/
	using ByteTag = ValueWarpperTag<std::byte>; /**< Byte tag. */
	using Int16Tag = ValueWarpperTag<std::int16_t>; /**< Signed 16 bit int tag. */
	using Int32Tag = ValueWarpperTag<std::int32_t>; /**< Signed 32 bit int tag. */
	using Uint32Tag = ValueWarpperTag<std::uint32_t>; /**< Unsigned 32 bit int tag. */
	using Int64Tag = ValueWarpperTag<std::int64_t>; /**< Signed 64 bit int tag. */
	using Uint64Tag = ValueWarpperTag<std::uint64_t>; /**< Unsigned 64 bit tag. */
	using FloatTag = ValueWarpperTag<float>; /**< Float tag. */
	using DoubleTag = ValueWarpperTag<double>; /**< Double tag. */
	using BooleanTag = ValueWarpperTag<bool>; /**< Boolean tag. */
	using StringTag = ValueWarpperTag<std::string>; /**< String tag. */

	using Vector2Tag = ValueWarpperTag<Vector2>; /**< vas::Vector2 tag. */

	using ObjectListTag = ArrayTag<std::shared_ptr<ITag>>; /**< Array of NBT tags. */

	/** @} */
}