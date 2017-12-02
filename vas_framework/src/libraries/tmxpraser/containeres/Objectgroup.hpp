#pragma once
#include <string>
#include <vector>
#include "Object.hpp"

namespace vas
{
	class Objectgroup : public std::vector<vas::Object>
	{
	public:
		Objectgroup();
		~Objectgroup();

		Object& operator[](const std::wstring& name);
		const Object& operator[](const std::wstring& name) const;

		Object& operator[](size_t index);
		const Object& operator[](size_t index) const;

		Object* find(const std::wstring& name, const std::wstring& type);
		const Object* find(const std::wstring& name, const std::wstring& type) const;
	};
}