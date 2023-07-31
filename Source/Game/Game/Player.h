#pragma once
#include "Framework/Actor.h"
#include "Mewmont.h"

class Player : public ringo::Actor {
public:
	Player(const ringo::Transform& transform, std::shared_ptr<ringo::Model> model, Mewmont* game) :
		Actor{ transform, model },
		m_game{ game } {}
	Player(float speed, float turnRate, const ringo::Transform& transform, std::shared_ptr<ringo::Model> model, Mewmont* game) :
		Actor{ transform, model },
		m_speed{ speed },
		m_turnRate{ turnRate },
		m_game { game } {}
	void Update(float dt) override;
	void OnCollision(Actor* other) override;
private:
	float m_speed = 0;
	float m_turnRate = 0;
	Mewmont* m_game;
};