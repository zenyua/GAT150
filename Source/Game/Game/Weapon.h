#pragma once
#include "Framework/Actor.h"
class Weapon : public ringo::Actor {
public:
	//, std::shared_ptr<ringo::Model> model was removed
	Weapon(float speed, const ringo::Transform& transform) :
		Actor{ transform }, //, model
		m_speed{ speed }
	{
		m_lifespan = 10.0f;
	}
	void Update(float dt) override;
	void OnCollision(Actor* other) override;
private:
	float m_speed = 0;
};