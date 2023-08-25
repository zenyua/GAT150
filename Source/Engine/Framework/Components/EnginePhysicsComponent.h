#pragma once
#include "PhysicsComponent.h"

namespace ringo {
	class EnginePhysicsComponent : public PhysicsComponent {
	public:
		CLASS_DECLARATION(EnginePhysicsComponent)

		void Update(float dt) override;
		void ApplyForce(const vec2& force) override;
		void ApplyTorque(float torque) override;
	};
}