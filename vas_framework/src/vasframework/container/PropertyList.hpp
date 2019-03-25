//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <vector>
#include "Property.hpp"

namespace vas
{
	/**
	 * @ingroup container
	 * @{
	 */
	/**
	 * @brief A list of properties.
	 * 
	 * A list or an array of properties. It store multiple properties at the same time.
	 */
	class VAS_DECLSPEC PropertyList : public std::vector<Property>
	{ /** @} */
	public:
		PropertyList();
		PropertyList(const PropertyList& rhs);
		PropertyList(PropertyList&& rhs) noexcept;
		PropertyList(std::initializer_list<Property> list); /**< Create a PropertyList with initializer_list. */
		~PropertyList();

		/**
		 * Find a property with its name, throw std::out_of_range if error.
		 * @param[in] name Name of the property.
		 * @return The related property.
		 * @throw std::out_of_range if @p name is not located.
		 * @warning This function will have linear time cost _o(n)_.
		 */
		Property& find(const std::string& name);
		/**
		 * Find a const property with its name, throw std::out_of_range if error.
		 * @param[in] name Name of the property.
		 * @return The related property.
		 * @throw std::out_of_range if @p name is not located.
		 * @warning This function will have linear time cost _o(n)_.
		 */
		const Property& find(const std::string& name) const;

		PropertyList& operator=(const PropertyList&) = default;
		PropertyList& operator=(PropertyList&& rhs) noexcept;
		/**
		 * @name Overloaded operators
		 * @{
		 */
		PropertyList& operator=(std::initializer_list<Property> list); /**< Iniitialize a PropertyList with initializer_list. */

		/**
		 * Find a property with its name.
		 * @param[in] name Name of the property.
		 * @return reference to the related property.
		 * @throw std::out_of_range if @p name is not located.
		 * @warning This function will have linear time cost _o(n)_.
		 */
		Property& operator[](const std::string& name);
		/**
		 * Find a property with its name.
		 * @param[in] name Name of the property.
		 * @return Const reference to the related property.
		 * @throw std::out_of_range if @p name is not located.
		 * @warning This function will have linear time cost _o(n)_.
		 */
		const Property& operator[](const std::string& name) const;
		/**
		 * Find a property with its index.
		 * @param[in] index Index of the property.
		 * @return reference to the related property.
		 * @throw std::out_of_range if @p index is larger or equal to the size of list.
		 */
		Property& operator[](size_t index);
		/**
		 * Find a property with its index.
		 * @param[in] index Index of the property.
		 * @return Const reference to the related property.
		 * @throw std::out_of_range if @p index is larger or equal to the size of list.
		 */
		const Property& operator[](size_t index) const;
		/** @} */
	private:
		using super = std::vector<Property>;
	};
}