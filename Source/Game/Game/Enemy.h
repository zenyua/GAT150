#pragma once
#include "Framework/Actor.h"
class Enemy : public ringo::Actor {
public:
	Enemy(float speed, float turnRate, const ringo::Transform& transform, std::shared_ptr<ringo::Model> model) :
		Actor{ transform, model },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{
		m_fireRate = 2.0f, m_fireTimer = m_fireRate;
	}
	void Update(float dt) override;
	void OnCollision(Actor* other) override;
private:
	float m_speed = 0;
	float m_turnRate = 0;

	float m_fireRate = 0;
	float m_fireTimer = 0;
};