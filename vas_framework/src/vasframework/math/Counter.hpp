//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <cstdint>
#include "../VASConfig.hpp"

namespace vas
{
	/**
	 * @ingroup math
	 * @{
	 */
	/**
	 * @brief Counting to the limit.
	 * 
	 * The Counter is an object that does the counting jobs. It will reset itself automaticaly once it reach the limit of the
	 * counter set by user. The defalut of the limit is the maximum of size_t data type.
	 */
	class VAS_DECLSPEC Counter
	{ /** @} */
	public:
		/** Create Counter with default limit. */
		Counter() = default;
		/**
		 * Create Counter with user specified limit.
		 * @param[in] autoResetLimit Ticks that when the counter reset it self.
		 */
		explicit Counter(size_t autoResetLimit);

		/**
		 * Set the limit ticks of the counter.
		 * @param[in] autoResetLimit new ticks limit.
		 */
		void setAutoResetLimit(size_t autoResetLimit);
		/** Reset the counter to zero. */
		void reset();

		size_t getMaxTick() const; /**< Get the maximum ticks that the counter can count, usualy counter's limit - 1. */
		size_t getLimit() const; /**< Get the limit of the counter*/

		Counter& operator++(int); /**< Increment of the counter. */
		Counter& operator--(int); /**< Decrement of the counter. */

		bool operator==(const Counter& rhs);
		bool operator==(const size_t& rhs);

		operator size_t&(); /**< Inplicitly casting the counter to size_t, use to get the current count of the counter. */
		operator const size_t&() const; /**< As Counter::operator size_t&(), but with const modifier. */
	private:
		size_t ticks{ 0 };
		size_t autoResetLimit{ SIZE_MAX };
	};
}