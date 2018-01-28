#pragma once
#include <cstdint>
#include "../VASConfig.hpp"

namespace vas
{
	class VAS_DECLSPEC Counter
	{
	public:
		Counter();
		Counter(size_t autoResetLimit);
		~Counter();

		void setAutoResetLimit(size_t autoResetLimit);
		void reset();

		Counter& operator++(int);
		Counter& operator--(int);

		bool operator==(const Counter& rhs);
		bool operator==(const size_t& rhs);

		operator size_t&();
	private:
		size_t ticks = 0;
		size_t autoResetLimit = SIZE_MAX;
	};
}