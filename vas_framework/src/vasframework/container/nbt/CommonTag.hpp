//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
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

	  The NBT(Named Binary Tag) structure is a serializeable tree like data structure with multiple data entrys. The tree
	  own the tree or array (also called list) as the brach of the tree and data tags as leaves.

	  The core components of NBT tags as bellow are able to included together by the header "vasframework/container/nbt/NBT.hpp"
	  
	  - NBTCompoundTag
	  - ValueWrapperTag
	  - ArrayTag
	  - ByteTag
	  - Int16Tag
	  - Int32Tag
	  - Uint32Tag
	  - Int64Tag
	  - Uint64Tag
	  - FloatTag
	  - DoubleTag
	  - BooleanTag
	  - StringTag
	  - Vector2Tag
	  - ObjectListTag
	  - ITag interface
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
	class ValueWrapperTag : public ITag
	{ /** @} */
	public:
		using TagType = ValueType; /**< bType of the wrapper emulated. */
		ValueWrapperTag() = default;
		/** Copy constructor. */
		ValueWrapperTag(const ValueType& value) : value(value)
		{
		}

		/** Move constructor. */
		ValueWrapperTag(ValueType&& value) : value(std::move(value))
		{
		}

		/** Create new instance of tag, use with list initialization.
			  @retval std::unique_ptr<ValueWrapperTag> new instance of tag.
		*/
		static std::unique_ptr<ValueWrapperTag> create()
		{
			return std::make_unique<ValueWrapperTag>();
		}

		/** Create new instance of tag with value, use with list initialization.
			  @param value Value to initialize the tag.
			  @retval std::unique_ptr<ValueWrapperTag> new instance of tag.
		*/
		static std::unique_ptr<ValueWrapperTag> create(ValueType value)
		{
			return std::make_unique<ValueWrapperTag>(std::move(value));
		}

		/** Convert wrapper to reference of ValueType. */
		operator ValueType&()
		{
			return value;
		}

		/** Convert wrapper to const reference of ValueType. */
		operator const ValueType&() const
		{
			return value;
		}

		/** Get the value of tag. */
		ValueType& get()
		{
			return const_cast<ValueType&>(const_cast<const ValueWrapperTag*>(this)->get());
		}
		
		/** Get the value of tag. */
		const ValueType& get() const
		{
			return value;
		}

		void serialize(const std::string& name, NBTSerializer& serializer) override
		{
			static_assert(std::numeric_limits<int>::is_specialized, "Non numeric data type must specialize member function ValueWrapperTag::serialize");
			serializer.accept(name, value);
		}
	private:
		ValueType value{};
	};

	/** @addtogroup nbt_tag
		  @{
	*/
	/** @brief An array or list of value.
		  @tparam T Type to store in array, must be serializeable if the feature required.
	*/
	template <class T>
	class ArrayTag : public ITag, public std::vector<T>
	{ /** @} */
	public:
		ArrayTag() = default;
		/** Create array with specified size.
			  @param size Size of the array.
		*/
		explicit ArrayTag(size_t size) : std::vector(size)
		{
		}

		/** Create array with iterator.
			  @param begin begin iterator hint.
			  @param end end iterator hint.
		*/
		template <class Iterator>
		ArrayTag(Iterator begin, Iterator end)
		{
			this->reserve(std::distance(begin, end));
			std::copy(begin, end, std::back_inserter(*this));
		}

		/** Initialize array with initializer list. */
		ArrayTag(std::initializer_list<T> list)
		{
			if (!this->empty())
			{
				this->clear();
				this->shrink_to_fit();
			}
			this->reserve(list.size());
			std::copy(list.begin(), list.end(), std::back_inserter(*this));
		}

		ArrayTag(const ArrayTag& rhs) : std::vector(rhs.begin(), rhs.end())
		{
		}

		ArrayTag(ArrayTag&& rhs) noexcept : std::vector(std::make_move_iterator(rhs.begin()), std::make_move_iterator(rhs.end))
		{
		}

		/** Create new instance of tag, use with list initialization.
			  @retval std::unique_ptr<ArrayTag> new instance of tag.
		*/
		static std::unique_ptr<ArrayTag> create()
		{
			return std::make_unique<ArrayTag>();
		}
		/** Create new instance of tag, use with list initialization.
			  @param list value to initialize the tag.
			  @retval std::unique_ptr<ArrayTag> new instance of tag.
		*/
		static std::unique_ptr<ArrayTag> create(std::initializer_list<T> list)
		{
			return std::make_unique<ArrayTag>(list);
		}

		void serialize(const std::string& name, NBTSerializer& serializer) override
		{
			static_assert(std::numeric_limits<T>::is_specialized, "T must be a valid numeric type to use default serialization, use a tag if it is able to represent in tag.");
			serializer.arrayStart(name);
			serializer.arraySizeSetter([this](size_t size) { this->resize(size); });
			for (size_t itr = 0; itr != this->size(); itr++)
				serializer.accept(boost::lexical_cast<std::string>(itr), this->at(itr));
			serializer.arrayEnd();
		}

		/** Assign from other ArrayTag. */
		ArrayTag& operator=(const ArrayTag& rhs)
		{
			this->clear();
			this->shrink_to_fit();
			this->reserve(rhs.size());
			std::copy(rhs.begin(), rhs.end(), std::back_inserter(this->begin()));
			return *this;
		}

		/** Move from other ArrayTag. */
		ArrayTag& operator=(ArrayTag&& rhs) noexcept
		{
			this->clear();
			this->reserve(rhs.size());
			for (auto& itr : rhs)
				this->push_back(std::move(itr));
			rhs.clear();
			return *this;
		}

		/** Swap with other ArrayTag. */
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
		for (size_t itr{ 0 }; itr != this->size(); itr++)
			this->at(itr)->serialize(boost::lexical_cast<std::string>(itr), serializer);
		serializer.arrayEnd();
	}

	template<>
	void ArrayTag<std::string>::serialize(const std::string& name, NBTSerializer& serializer)
	{
		serializer.arrayStart(name);
		serializer.arraySizeSetter([this](size_t size) { this->resize(size); });
		for (size_t itr = 0; itr != this->size(); itr++)
			serializer.accept(boost::lexical_cast<std::string>(itr), this->at(itr));
		serializer.arrayEnd();
	}

	template <>
	void ValueWrapperTag<std::string>::serialize(const std::string& name, NBTSerializer& serializer)
	{
		serializer.accept(name, value);
	}

	template <>
	void ValueWrapperTag<vas::Vector2>::serialize(const std::string& name, NBTSerializer& serializer)
	{
		serializer.arrayStart(name);
		serializer.accept("0", value.x);
		serializer.accept("1", value.y);
		serializer.arrayEnd();
	}

	/** @name Predefined tag
		  
		  The predefined tag that use with NBT structure. Include header "vasframework/container/nbt/CommonTag.hpp"
		  to access them.
		  @{
	*/
	using ByteTag = ValueWrapperTag<std::byte>; /**< Byte tag. */
	using Int16Tag = ValueWrapperTag<std::int16_t>; /**< Signed 16 bit int tag. */
	using Int32Tag = ValueWrapperTag<std::int32_t>; /**< Signed 32 bit int tag. */
	using Uint32Tag = ValueWrapperTag<std::uint32_t>; /**< Unsigned 32 bit int tag. */
	using Int64Tag = ValueWrapperTag<std::int64_t>; /**< Signed 64 bit int tag. */
	using Uint64Tag = ValueWrapperTag<std::uint64_t>; /**< Unsigned 64 bit tag. */
	using FloatTag = ValueWrapperTag<float>; /**< Float tag. */
	using DoubleTag = ValueWrapperTag<double>; /**< Double tag. */
	using BooleanTag = ValueWrapperTag<bool>; /**< Boolean tag. */
	using StringTag = ValueWrapperTag<std::string>; /**< String tag. */

	using Vector2Tag = ValueWrapperTag<Vector2>; /**< vas::Vector2 tag. */

	using ObjectListTag = ArrayTag<std::shared_ptr<ITag>>; /**< Array of NBT tags. */

	/** @} */
}