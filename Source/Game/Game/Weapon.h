#pragma once
#include "Framework/Actor.h"

class Weapon : public ringo::Actor {
public:
	Weapon(float speed, const ringo::Transform& transform) :
		Actor{ transform },
		m_speed{ speed }
	{
		m_lifespan = 30.0f;
	}

	bool Initialize() override;

	void Update(float dt) override;
	void OnCollision(Actor* other) override;
private:
	float m_speed = 0;
};