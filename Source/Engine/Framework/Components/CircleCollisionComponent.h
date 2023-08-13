#pragma once
#include "CollisionComponent.h"
namespace ringo {
	class CircleCollisionComponent : public CollisionComponent {
	public:
		

		// Inherited via CollisionComponent
		virtual void Update(float dt) override;

		virtual bool CheckCollision(CollisionComponent* collision) override;

	};
}