#pragma once
#include "Framework/Actor.h"
class Weapon : public ringo::Actor {
public:
	Weapon(float speed, const ringo::Transform& transform, std::shared_ptr<ringo::Model> model) :
		Actor{ transform, model },
		m_speed{ speed }
	{
		m_lifespan = 10.0f;
	}
	void Update(float dt) override;
	void OnCollision(Actor* other) override;
private:
	float m_speed = 0;
};