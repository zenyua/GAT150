#include "ContactListener.h"
#include "Framework/Actor.h"
#include "Framework/Components/CollisionComponent.h"

namespace ringo {
	void ContactListener::BeginContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA->GetUserData().pointer && fixtureB->GetUserData().pointer)
		{
			Actor* actorA = reinterpret_cast<Actor*>(fixtureA->GetUserData().pointer);
			Actor* actorB = reinterpret_cast<Actor*>(fixtureB->GetUserData().pointer);

			if (actorA->destroyed || actorB->destroyed) return;

			actorA->OnCollisionEnter(actorB);
			if(actorB) actorB->OnCollisionEnter(actorA);

		}
	}
	void ContactListener::EndContact(b2Contact* contact)
	{
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if (fixtureA->GetUserData().pointer && fixtureB->GetUserData().pointer)
		{
			Actor* actorA = reinterpret_cast<Actor*>(fixtureA->GetUserData().pointer);
			Actor* actorB = reinterpret_cast<Actor*>(fixtureB->GetUserData().pointer);

			if (actorA->destroyed || actorB->destroyed) return;

			if (!actorA) return;
			actorA->OnCollisionExit(actorB);
			if (!actorB) return;
			actorB->OnCollisionExit(actorA);

		}
	}
}