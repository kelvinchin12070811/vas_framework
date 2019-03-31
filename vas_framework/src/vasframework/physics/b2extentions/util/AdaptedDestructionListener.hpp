//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#pragma once
#include "../../../VASConfig.hpp"

#ifdef VAS_HAS_B2D
#include "../b2WorldEx.hpp"

namespace vas::physics::b2extentions
{
	class VAS_DECLSPEC AdaptedDestructionListener : public b2DestructionListener
	{
	public:
		void SayGoodbye(b2Joint* joint) override;
		void SayGoodbye(b2Fixture* fixture) override;
		b2WorldEx* world{ nullptr };
		b2DestructionListener* customListener{ nullptr };

	};
}
#endif // VAS_HAS_B2D
