#include "Enemy.h"
#include "Player.h"
#include "Weapon.h"
#include "Input/InputSystem.h"

#include "Renderer/Renderer.h"

#include "Framework/Framework.h"
namespace ringo {
	CLASS_DEFINITION(Enemy)
	bool Enemy::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<PhysicsComponent>();

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

	void Enemy::OnDestroy() {
		Actor::OnDestroy();
	}

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);

		vec2 forward = vec2{ 0,-1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player) {
			vec2 direction = player->transform.position - transform.position;
			//turn towards player
			float turnAngle = vec2::SignedAngle(forward, direction.Normalized());

			m_physicsComponent->ApplyTorque(turnAngle);

			//check if player is in front
			if (std::fabs(turnAngle) < DegreesToRadians(30.0f)) {
				//I see you!
			}
		}

		m_physicsComponent->ApplyForce(forward * speed);

		transform.position.x = ringo::Wrap(transform.position.x, (float)ringo::g_renderer.GetWidth());
		transform.position.y = ringo::Wrap(transform.position.y, (float)ringo::g_renderer.GetHeight());
	}

	void Enemy::OnCollision(Actor* other)
	{
		if (other->tag == "Weapon") {
			ringo::EventManager::Instance().DispatchEvent("AddPoints", 100);
			m_game->AddMoney(10);
			destroyed = true;
			ringo::EmitterData data;
			data.burst = true;
			data.burstCount = 100;
			data.spawnRate = 200;
			data.angle = 0;
			data.angleRange = ringo::Pi;
			data.lifetimeMin = 1.5f;
			data.speedMin = 50;
			data.speedMax = 250;
			data.damping = 0.5f;
			data.color = ringo::Color{ 1, 0, 0, 1 };
			ringo::Transform transform{ { this->transform.position }, 0, 1 };
			auto emitter = std::make_unique<ringo::Emitter>(transform, data);
			emitter->lifespan = 1.0f;
			m_scene->Add(std::move(emitter));
		}
		if (other->tag == "Player") {
			destroyed = true;
		}

	}

	void Enemy::Read(const json_t& value) {
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, turnRate);
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
