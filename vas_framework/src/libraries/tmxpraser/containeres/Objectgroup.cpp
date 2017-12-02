#include "Objectgroup.hpp"
#include <algorithm>
#include "../../VASFramework/util/TextTools.hpp"

namespace vas
{
	Objectgroup::Objectgroup()
	{
	}

	Objectgroup::~Objectgroup()
	{
	}

	Object & Objectgroup::operator[](const std::wstring & name)
	{
		return const_cast<Object&>(const_cast<const Objectgroup&>(*this)[name]);
	}

	const Object & Objectgroup::operator[](const std::wstring & name) const
	{
		auto result = std::find_if(this->begin(), this->end(), [&](const Objectgroup::value_type& value)->bool
		{
			return value.name == name;
		});

		if (result == this->end())
			throw std::out_of_range("Cannot find object \""s + TextTools::wstos(name) + "\""s);
		return *result;
	}

	Object & Objectgroup::operator[](size_t index)
	{
		return const_cast<Object&>(const_cast<const Objectgroup&>(*this)[index]);
	}

	const Object & Objectgroup::operator[](size_t index) const
	{
		if (index >= this->size())
			throw std::out_of_range("This objectgroup contains "s + std::to_string(this->size()) + " item but request item at "s + std::to_string(index));
		return this->at(index);
	}

	Object * Objectgroup::find(const std::wstring & name, const std::wstring & type)
	{
		return const_cast<Object*>(const_cast<const Objectgroup*>(this)->find(name, type));
	}

	const Object * Objectgroup::find(const std::wstring & name, const std::wstring & type) const
	{
		auto result = std::find_if(this->begin(), this->end(), [&](const Objectgroup::value_type& value)->bool
		{
			return (value.name == name) && (value.type == type);
		});

		return result == this->end() ? nullptr : result._Ptr;
	}
}