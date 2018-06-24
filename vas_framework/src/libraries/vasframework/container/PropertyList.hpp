#pragma once
#include <vector>
#include "Property.hpp"

namespace vas
{
	class VAS_DECLSPEC PropertyList : public std::vector<Property>
	{
	public:
		PropertyList();
		PropertyList(const PropertyList& rhs);
		PropertyList(PropertyList&& rhs);
		~PropertyList();

		Property& find(const std::string& name);
		const Property& find(const std::string& name) const;

		PropertyList& operator=(const PropertyList&) = delete;
		PropertyList& operator=(PropertyList&& rhs);
		PropertyList& operator=(std::initializer_list<Property> list);

		Property& operator[](const std::string& name);
		const Property& operator[](const std::string& name) const;

		Property& operator[](size_t index);
		const Property& operator[](size_t index) const;
	private:
		using super = std::vector<Property>;
	};
}