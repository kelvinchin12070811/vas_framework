#pragma once
#include "../VASConfig.hpp"

namespace vas
{
	class VAS_DECLSPEC Boolean
	{
	public:
		Boolean();
		Boolean(bool state);
		Boolean(const Boolean& rhs);

		bool operator==(const Boolean& rhs) const;
		bool operator==(bool rhs) const;
		bool operator!=(const Boolean& rhs) const;
		bool operator!=(bool rhs) const;

		Boolean& operator=(bool rhs);
		Boolean& operator=(const Boolean& rhs);

		explicit operator bool&();
		explicit operator const bool&() const;
	private:
		bool value = false;
	};
}