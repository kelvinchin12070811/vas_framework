//======================================================================
//This Source Code Form is subject to the terms of the Mozilla Public
//License, v. 2.0. If a copy of the MPL was not distributed with this
//file, You can obtain one at https://mozilla.org/MPL/2.0/.
//======================================================================
#include "AdaptedDestructionListener.hpp"

#ifdef VAS_HAS_B2D
namespace vas::physics::b2extentions
{
	void AdaptedDestructionListener::SayGoodbye(b2Joint * joint)
	{
		if (customListener) customListener->SayGoodbye(joint);
		world->MarkObjectDeath(reinterpret_cast<void*>(joint));
	}
	
	void AdaptedDestructionListener::SayGoodbye(b2Fixture * fixture)
	{
		if (customListener) customListener->SayGoodbye(fixture);
		world->MarkObjectDeath(reinterpret_cast<void*>(fixture));
	}
}
#endif // VAS_HAS_B2D