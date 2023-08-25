#include "Enemy.h"
#include "Player.h"
#include "Weapon.h"
#include "Input/InputSystem.h"

#include "Renderer/Renderer.h"

#include "Framework/Framework.h"
//put in namespace
//class_definition macro
bool Enemy::Initialize()
{
	Actor::Initialize();
	auto collisionComponent = GetComponent<ringo::CollisionComponent>();
	if (collisionComponent) {
		auto spriteComponent = GetComponent<ringo::SpriteComponent>();
		if (spriteComponent) {
			float scale = transform.scale;
			collisionComponent->m_radius = spriteComponent->GetRadius() * scale;
		}
	}

	return true;
}

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	Player* player = m_scene->GetActor<Player>();
	
	ringo::vec2 direction{ 0, 0 };

	if (player) {
		if (player->transform.position.x > transform.position.x) {
			direction.x++;
		} else {
			direction.x--;
		}
		if (player->transform.position.y > transform.position.y) {
			direction.y++;
		}
		else {
			direction.y--;
		}
	}

	if (player) {
		ringo::Vector2 direction = player->transform.position - transform.position;
		transform.rotation = direction.Angle() + ringo::HalfPi;
	}

	transform.position = transform.position + (direction * speed * dt);

	transform.position.x = ringo::Wrap(transform.position.x, (float)ringo::g_renderer.GetWidth());
	transform.position.y = ringo::Wrap(transform.position.y, (float)ringo::g_renderer.GetHeight());
}

void Enemy::OnCollision(Actor* other)
{
	//when he dies...
	ringo::EventManager::Instance().DispatchEvent("AddPoints", 100);
	if (other->tag == "Weapon") {
		//m_game->AddPoints(100);
		m_game->AddMoney(10);
		destroyed = true;
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
		ringo::Transform transform{ { transform.position }, 0, 1 };
		auto emitter = std::make_unique<ringo::Emitter>(transform, data);
		emitter->lifespan = 1.0f;
		m_scene->Add(std::move(emitter));
	}
	if (other->tag == "Player") {
		destroyed = true;
	}
	
}

//if (player) {
	//	ringo::Vector2 direction = player->transform.position - transform.position;
	//	transform.rotation = direction.Angle() + ringo::HalfPi;
	//}
	////fire weapon when timer reaches 0, then reset the timer to the firerate
	//m_fireTimer--;
	///*if (m_fireTimer <= 0) {
	//	ringo::Transform transform{transform.position, transform.rotation, 1};
	//	std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400, transform, m_model);
	//	m_scene->Add(std::move(weapon));
	//	m_fireTimer = m_fireRate;
	//}*/

	//ringo::vec2 forward = ringo::vec2{ 0, -1 }.Rotate(transform.rotation);
	//transform.position += forward * speed * ringo::g_time.GetDeltaTime();
	//transform.position.x = ringo::Wrap(transform.position.x, (float)ringo::g_renderer.GetWidth());
	//transform.position.y = ringo::Wrap(transform.position.y, (float)ringo::g_renderer.GetHeight());
