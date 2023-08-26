#pragma once
#include "Framework/Actor.h"
#include <Core/Json.h>
namespace ringo {
	class Weapon : public Actor {
	public:
		CLASS_DECLARATION(Weapon) 
		bool Initialize() override;
		void Update(float dt) override;

		void OnCollision(Actor* other);
	private:
		float speed = 0;
	};
}