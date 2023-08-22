#pragma once
#include "Framework/Actor.h"
#include <Core/Json.h>
namespace ringo {
	class Weapon : public Actor {
	public:
		CLASS_DECLARATION(Weapon) //maybe needs namespace?
		bool Initialize() override;
		void Update(float dt) override;

		void OnCollision(Actor* other);
		//void Read(const json_t& value) override; //included in the class_declaration
	private:
		float speed = 0;
	};
}