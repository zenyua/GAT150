#include "Enemy.h"
#include "Player.h"
#include "Weapon.h"
#include "Input/InputSystem.h"
#include "Framework/Scene.h"
#include "Framework/Emitter.h"

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	Player* player = m_scene->GetActor<Player>();
	
	ringo::vec2 direction{ 0, 0 };

	if (player) {
		if (player->m_transform.position.x > m_transform.position.x) {
			direction.x++;
		} else {
			direction.x--;
		}
		if (player->m_transform.position.y > m_transform.position.y) {
			direction.y++;
		}
		else {
			direction.y--;
		}
	}

	if (player) {
		ringo::Vector2 direction = player->m_transform.position - m_transform.position;
		m_transform.rotation = direction.Angle() + ringo::HalfPi;
	}

	m_transform.position = m_transform.position + (direction * m_speed * dt);

	m_transform.position.x = ringo::Wrap(m_transform.position.x, (float)ringo::g_renderer.GetWidth());
	m_transform.position.y = ringo::Wrap(m_transform.position.y, (float)ringo::g_renderer.GetHeight());
}

void Enemy::OnCollision(Actor* other)
{
	if (other->m_tag == "Weapon") {
		m_game->AddPoints(100);
		m_game->AddMoney(10);
		m_destroyed = true;
		ringo::EmitterData data;
		data.burst = true;
		data.burstCount = 100;
		data.spawnRate = 200;
		data.angle = 0;
		data.angleRange = ringo::Pi;
		data.lifetimeMin = 0.5f;
		data.lifetimeMin = 1.5f;
		data.speedMin = 50;
		data.speedMax = 250;
		data.damping = 0.5f;
		data.color = ringo::Color{ 1, 0, 0, 1 };
		ringo::Transform transform{ { m_transform.position }, 0, 1 };
		auto emitter = std::make_unique<ringo::Emitter>(transform, data);
		emitter->m_lifespan = 1.0f;
		m_scene->Add(std::move(emitter));
	}
	if (other->m_tag == "Player") {
		m_destroyed = true;
	}
	
}

//if (player) {
	//	ringo::Vector2 direction = player->m_transform.position - m_transform.position;
	//	m_transform.rotation = direction.Angle() + ringo::HalfPi;
	//}
	////fire weapon when timer reaches 0, then reset the timer to the firerate
	//m_fireTimer--;
	///*if (m_fireTimer <= 0) {
	//	ringo::Transform transform{m_transform.position, m_transform.rotation, 1};
	//	std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400, m_transform, m_model);
	//	m_scene->Add(std::move(weapon));
	//	m_fireTimer = m_fireRate;
	//}*/

	//ringo::vec2 forward = ringo::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	//m_transform.position += forward * m_speed * ringo::g_time.GetDeltaTime();
	//m_transform.position.x = ringo::Wrap(m_transform.position.x, (float)ringo::g_renderer.GetWidth());
	//m_transform.position.y = ringo::Wrap(m_transform.position.y, (float)ringo::g_renderer.GetHeight());
