#pragma once
#include "Framework/Actor.h"

class Tower : public ringo::Actor {
public:
	Tower(float fireRate, const ringo::Transform& transform) :
		Actor{ transform },
		m_fireRate{ fireRate } 
	{
		weaponTransform.scale = 1;
	}
	void Update(float dt) override;
private:
	float m_fireRate = 0;
	float m_fireTimer = 0;
	ringo::Transform weaponTransform = m_transform;
};