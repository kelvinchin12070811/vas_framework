#pragma once
#include <boost/any.hpp>

namespace vas
{
	class Property
	{
	public:
		Property();
		Property(const std::string& name, const boost::any& value);
		Property(const std::string& name, boost::any&& value);
		Property(const Property& rhs);
		Property(Property&& rhs);
		~Property();

		const std::type_info& type() const;
		bool empty() const;
		void swap(Property& rhs);
		void clear();

		template <typename OutputType>
		OutputType* get();
		template <typename OutputType>
		const OutputType* get() const;

		explicit operator boost::any&();
		explicit operator const boost::any&() const;
		
		Property& operator=(const Property& rhs);
		Property& operator=(Property&& rhs);
		Property& operator=(const boost::any& rhs);
		Property& operator=(boost::any&& rhs);

		//Compare function, function as 'operator=='
		template <typename T>
		bool isEqual(const Property& rhs) const;
		//Compare function, function as 'operator!='
		template <typename T>
		bool notEqual(const Property& rhs) const;
	private:
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
		if (this->type() != rhs.type()) return false;
		if (*this->get<T>() != *rhs.get<T>()) return false;
		return true;
	}

	template<typename T>
	inline bool Property::notEqual(const Property & rhs) const
	{
		if (this->type() != rhs.type()) return true;
		if (*this->get<T>() != *rhs.get<T>()) return true;
		return false;
	}
}