#pragma once
#include "../VASConfig.hpp"

#ifndef on
#define on true
#endif // !on
#ifndef off
#define off false
#endif // !off

namespace vas
{
	class VAS_DECLSPEC Switch
	{
	public:
		Switch();
		Switch(bool state);
		~Switch();

		operator bool() const;
		explicit operator std::string() const;

		bool operator==(const Switch& rhs) const;
		bool operator==(bool rhs) const;
		bool operator!=(const Switch& rhs) const;
		bool operator!=(bool rhs) const;
	private:
		bool value = false;
	};
}