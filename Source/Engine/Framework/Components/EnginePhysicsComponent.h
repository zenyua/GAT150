#pragma once
#include "PhysicsComponent.h"

namespace ringo {
	class EnginePhysicsComponent : public PhysicsComponent {
	public:
		void Update(float dt) override;
		void ApplyForce(const vec2 force);
	};
}