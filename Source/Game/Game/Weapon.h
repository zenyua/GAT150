#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"
#include <Core/Json.h>
namespace ringo {
	class Weapon : public Actor {
	public:
		CLASS_DECLARATION(Weapon) 
		bool Initialize() override;
		void Update(float dt) override;

		void OnCollisionEnter(Actor* other);
	private:
		float speed = 0;
		PhysicsComponent* m_physicsComponent = nullptr;
	};
}