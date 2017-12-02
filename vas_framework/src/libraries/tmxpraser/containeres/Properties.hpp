#pragma once
#include <vector>
#include "Property.hpp"

namespace vas
{
	class Properties : public std::vector<Property>
	{
	public:
		Properties();
		~Properties();

		Property& operator[](size_t index);
		const Property& operator[](size_t index) const;

		Property& operator[](const std::wstring& name);
		const Property& operator[](const std::wstring& name) const;
	};
}