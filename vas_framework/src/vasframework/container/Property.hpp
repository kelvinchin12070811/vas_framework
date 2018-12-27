#pragma once
#include <boost/any.hpp>
#include "../sreflex/Util.hpp"
#include "../VASConfig.hpp"

namespace vas
{
	/** @addtogroup container
		  @{
	*/
	/** @brief The property of an object.

		  The property can store any type of data. The Property class is the property of the object instances, it does related to
		  the class.
	*/
	class VAS_DECLSPEC Property
	{ /** @} */
	public:
		Property();
		/** Create property with name and value.
			  @param name Name of the property.
			  @param value Value that this property will store.
		*/
		Property(const std::string& name, const boost::any& value);
		/** Create property with name and value.
			 @param name Name of the property.
			 @param value Value that this property will store (moved).
		*/
		Property(const std::string& name, boost::any&& value);
		Property(const Property& rhs);
		Property(Property&& rhs) noexcept;
		~Property();

		const boost::typeindex::type_index type() const; /**< Get the type of the data stored. */
		bool empty() const; /**< Check if the property is empty. */
		/** Swap two Property.
			  @param rhs Target property to swap.
		*/
		void swap(Property& rhs);
		/** Clear the property entries.
		*/
		void clear();

		void setName(const std::string& name);
		std::string getName() const;

		/** @memberof Property
			  Get the pointer to the value stored in property.
			  @tparam OutputType Type of the value to extract. Must be same as Property::type().
			  @return Pointer to the value if success, nullptr if failed.
		*/
		template <typename OutputType>
		OutputType* get();
		/** @memberof Property
			  Get the const pointer to the value stored in property.
			  @tparam OutputType Type of the value to extract. Must be same as Property::type().
			  @return Pointer to the value if success, nullptr if failed.
		*/
		template <typename OutputType>
		const OutputType* get() const;

		operator boost::any&(); /**< Convert to boost::any implicitly. */
		operator const boost::any&() const; /**< Convert to boost::any implicitly with const modifier. */
		
		Property& operator=(const Property& rhs);
		Property& operator=(Property&& rhs) noexcept;
		/** @name Overloaded operators
			  @{
		*/
		Property& operator=(const boost::any& rhs); /**< Assign a boost::any to property. */
		Property& operator=(boost::any&& rhs) noexcept; /**< Move a boost::any to property. */
		/** @} */

		//Compare function, function as 'operator=='
		template <typename T>
		bool isEqual(const Property& rhs) const;
		//Compare function, function as 'operator!='
		template <typename T>
		bool notEqual(const Property& rhs) const;
	private:
		/** [Read & Write] The name of the property.

			  - __mutators__
				-# void setName(const std::string& name)
			  - __accessors__
				-# std::string getName() const
		*/
		std::string name;
		boost::any value;
	};

	template<typename OutputType>
	inline OutputType * Property::get()
	{
		return boost::any_cast<OutputType>(&this->value);
	}

	template<typename OutputType>
	inline const OutputType * Property::get() const
	{
		return boost::any_cast<OutputType>(&this->value);
	}

	template<typename T>
	inline bool Property::isEqual(const Property & rhs) const
	{
		using namespace std::string_literals;
		if (this->type() != boost::typeindex::type_id<T>()) throw std::runtime_error{ "Unable to compate different type of value: "s + sreflex::simpliflyObjectNameCpy(this->type().pretty_name()) + " != " + sreflex::getObjectName<T>() };
		if (this->type() != rhs.type()) return false;
		if (*this->get<T>() != *rhs.get<T>()) return false;
		return true;
	}

	template<typename T>
	inline bool Property::notEqual(const Property & rhs) const
	{
		using namespace std::string_literals;
		if (this->type() != boost::typeindex::type_id<T>()) throw std::runtime_error{ "Unable to compate different type of value: "s + sreflex::simpliflyObjectNameCpy(this->type().pretty_name()) + " != " + sreflex::getObjectName<T>() };
		if (this->type() != rhs.type()) return true;
		if (*this->get<T>() != *rhs.get<T>()) return true;
		return false;
	}
}