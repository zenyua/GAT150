#include "Tower.h"

#include "Weapon.h"
#include "Framework/Scene.h"

void Tower::Update(float dt) {

	Actor::Update(dt);

	m_fireTimer -= dt;
	
	if (m_fireTimer <= 0) {
		/*std::unique_ptr<ringo::Weapon> weapon = std::make_unique<ringo::Weapon>(40.0f, weaponTransform);
		weapon->tag = "Weapon";
		m_scene->Add(std::move(weapon));*/

		m_fireTimer = m_fireRate;
	}

}