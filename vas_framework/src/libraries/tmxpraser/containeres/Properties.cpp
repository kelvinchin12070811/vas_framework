#include "Properties.hpp"
#include <algorithm>
#include "../../VASFramework/util/TextTools.hpp"

namespace vas
{
	Properties::Properties()
	{
	}

	Properties::~Properties()
	{
	}

	Property & Properties::operator[](size_t index)
	{
		return const_cast<Property&>(const_cast<const Properties&>(*this)[index]);
	}

	const Property & Properties::operator[](size_t index) const
	{
		if (index >= this->size())
			throw std::out_of_range("This properties contain "s + std::to_string(this->size()) + " item but request item at "s + std::to_string(index));
		return this->at(index);
	}

	Property & Properties::operator[](const std::wstring & name)
	{
		return const_cast<Property&>(const_cast<const Properties&>(*this)[name]);
	}

	const Property & Properties::operator[](const std::wstring & name) const
	{
		auto result = std::find_if(this->begin(), this->end(), [&](const Property& value)->bool {
			return value.getName() == name;
		});

		if (result == this->end())
			throw std::out_of_range("Cannot find the value with the name \""s + TextTools::wstos(name) + "\""s);
		return *result;
	}
}