#include "Tower.h"

#include "Weapon.h"
#include "Framework/Scene.h"

void Tower::Update(float dt) {

	Actor::Update(dt);

	m_fireTimer -= dt;
	
	if (m_fireTimer <= 0) {
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(40.0f, weaponTransform);
		weapon->m_tag = "Weapon";
		m_scene->Add(std::move(weapon));

		m_fireTimer = m_fireRate;
	}

}