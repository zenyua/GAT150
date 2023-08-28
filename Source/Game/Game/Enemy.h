#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace ringo {
	class Enemy : public Actor {
	public:
		CLASS_DECLARATION(Enemy)

		bool Initialize() override;
		void OnDestroy() override;
		void Update(float dt) override;

		void OnCollisionEnter(Actor* other) override;
	public:
		float speed = 0;
		float turnRate = 0;

		float fireRate = 0;
		float fireTimer = 0;

		ringo::PhysicsComponent* m_physicsComponent = nullptr;
	};
}