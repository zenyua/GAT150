#pragma once
#include "Framework/Actor.h"
#include "Mewmont.h"
#include <Framework/Components/PhysicsComponent.h>
namespace ringo {
	class Player : public Actor {
	public:
		CLASS_DECLARATION(Player)
		/*Player(const ringo::Transform& transform, Mewmont* game) :
			Actor{ transform },
			m_game{ game } {}
		Player(float speed, float turnRate, const ringo::Transform& transform, Mewmont* game) :
			Actor{ transform },
			speed{ speed },
			turnRate{ turnRate },
			m_game { game } {}*/

		bool Initialize() override;

		void Update(float dt) override;
		void OnCollision(Actor* other) override;
	private:
		float speed = 0;
		float turnRate = 0;
		Mewmont* m_game;

		ringo::PhysicsComponent* m_physicsComponent = nullptr;
	};
}