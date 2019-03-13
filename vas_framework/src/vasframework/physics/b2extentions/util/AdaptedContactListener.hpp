#pragma once
#include "../b2WorldEx.hpp"
#ifdef VAS_HAS_B2D
namespace vas::physics::b2extentions
{
	class AdaptedContactListener : public b2ContactListener
	{
	public:
		void BeginContact(b2Contact* contact) override;
		void EndContact(b2Contact* contact) override;
		void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
		void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;
	private:
		b2WorldEx* world{ nullptr };
		b2ContactListener* customListener{ nullptr };

		friend b2WorldEx;
	};
}
#endif // VAS_HAS_B2D