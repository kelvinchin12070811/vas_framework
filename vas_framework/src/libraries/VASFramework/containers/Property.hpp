#pragma once
#include <string>
#include <boost/lexical_cast.hpp>

using namespace std::literals::string_literals;

namespace vas
{
	class Property
	{
	public:
		Property(const std::wstring& name, const std::wstring& value = L""s);
		template <typename ValueType>
		Property(const std::wstring& name, const ValueType& value = L""s);
		Property(const Property& other);
		Property(Property&& other);
		~Property();
		
		const std::wstring& getRaw(const std::wstring& def = L""s) const;
		const std::wstring& getName() const;

		Property& operator=(const Property& rhs);
		Property& operator=(Property&& rhs);

		template<typename OutputType>
		inline OutputType get() const;

		template<typename OutputType>
		inline OutputType get(OutputType def) const;
	private:
		std::wstring name;
		std::wstring value;
	};

	template<typename ValueType>
	inline Property::Property(const std::wstring & name, const ValueType & value):
		Property(name, boost::lexical_cast<std::wstring>(value))
	{
	}

	template<typename OutputType>
	inline OutputType Property::get() const
	{
		try
		{
			return boost::lexical_cast<OutputType>(getRaw());
		}
		catch (const boost::bad_lexical_cast&)
		{
			return OutputType();
		}
	}

	template<typename OutputType>
	inline OutputType Property::get(OutputType def) const
	{
		try
		{
			return boost::lexical_cast<OutputType>(getRaw());
		}
		catch (boost::bad_lexical_cast&)
		{
			return def;
		}
	}
}