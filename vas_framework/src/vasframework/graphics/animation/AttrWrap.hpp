//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include <functional>
#include "../../sdlcore/math/Colour.hpp"

namespace vas
{
	/**
	 * @ingroup animate
	 * @{
	 */
	/**
	 * @brief The wraper of the numeric attribute of object.
	 */
	template <typename AttrType, typename GetRetType = void>
	struct AttrWrap
	{ /** @} */
		using WrappedType = AttrType;
		/**
		 * Create wrapper of setter
		 * @param[in] mutator Function pointer to the setter of object.
		 */
		AttrWrap(std::function<void(AttrType)> mutator) : mutator(mutator), accessor(nullptr) {}
		AttrWrap(std::function<void(AttrType)> mutator, std::function<GetRetType()> accessor):
			mutator(mutator), accessor(accessor) {}
		
		/** Access the setter. */
		void operator()(double value)
		{
			if (mutator == nullptr)
				throw std::logic_error{ "Attribute 'mutator' cannot be nullptr." };
			if (accessor != nullptr)
			{
				auto&& value = accessor();
				value = static_cast<AttrType>(value);
				mutator(value);
			}
			else
			{
				if (!std::is_void<GetRetType>::value)
					throw std::logic_error{
						"Attribute 'accessor' with not void as return type must not be nullptr"
					};
				mutator(static_cast<AttrType>(value));
			}
		}
	protected:
		std::function<void(AttrType)> mutator;
		std::function<GetRetType()> accessor;
	};

	template<>
	struct AttrWrap<sdl::Colour, void>
	{
		enum class ColourChannel : uint8_t {
			red,
			green,
			blue,
			alpha
		};
		AttrWrap(std::function<void(const sdl::Colour&)> mut, std::function<sdl::Colour()> acc,
			ColourChannel channel = ColourChannel::alpha) :
			mutator(mut), accessor(acc), channel(channel) {}

		void operator()(double value)
		{
			sdl::Colour res = accessor();
			uint8_t* colour = nullptr;
			if (auto con = [&](auto&& c) { return channel == c; }; con(ColourChannel::red))
				colour = &res.red;
			else if (con(ColourChannel::green))
				colour = &res.green;
			else if (con(ColourChannel::blue))
				colour = &res.bule;
			else if (con(ColourChannel::alpha))
				colour = &res.alpha;
			else
				throw std::logic_error{ "Channel not valid." };

			*colour = static_cast<uint8_t>(value);
			mutator(res);
		}
	protected:
		std::function<void(const sdl::Colour&)> mutator;
		std::function<sdl::Colour()> accessor;
		ColourChannel channel{ ColourChannel::alpha };
	};
}