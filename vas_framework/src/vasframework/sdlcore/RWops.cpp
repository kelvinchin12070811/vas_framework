//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "RWops.hpp"

namespace vas::sdl
{
	namespace rwops
	{
		const uint32_t Type::unknow{ SDL_RWOPS_UNKNOWN };
		const uint32_t Type::winFile{ SDL_RWOPS_WINFILE };
		const uint32_t Type::stdFile{ SDL_RWOPS_STDFILE };
		const uint32_t Type::jniFile{ SDL_RWOPS_JNIFILE };
		const uint32_t Type::memory{ SDL_RWOPS_MEMORY };
		const uint32_t Type::readOnlyMemory{ SDL_RWOPS_MEMORY_RO };

		const int Whence::set{ 0 };
		const int Whence::cur{ 1 };
		const int Whence::end{ 2 };

		void VAS_DECLSPEC close(RWops * instance)
		{
			instance->close(instance);
		}
	}
}