#include "Player.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Weapon.h"
#include "Framework/Scene.h"
#include "Core/Core.h"
#include <Framework/Components/SpriteComponent.h>
#include <Framework/Components/PhysicsComponent.h>
#include <Framework/Resource/ResourceManager.h>
#include <Framework/Components/CircleCollisionComponent.h>
namespace ringo {
	CLASS_DEFINITION(Player)
	bool Player::Initialize() {
		Actor::Initialize();

		//cache off
		m_physicsComponent = GetComponent<ringo::PhysicsComponent>();
		auto collisionComponent = GetComponent<ringo::CollisionComponent>();
		if (collisionComponent) {
			auto spriteComponent = GetComponent<ringo::SpriteComponent>();
			if (spriteComponent) {
				float scale = transform.scale;
				collisionComponent->m_radius = spriteComponent->GetRadius() * scale * 0.75f;
			}
		}

		return true;
	}

	void Player::Update(float dt)
	{
		Actor::Update(dt);

		//rotate ship
		//we're not supposed to do the rotation on our own here, that's b2's responsibility. so just keep the sprite stuff?
		float rotate = 0;
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) {
			rotate = -1;
			GetComponent<ringo::SpriteComponent>()->m_texture = GET_RESOURCE(ringo::Texture, "KirbyA.png", ringo::g_renderer);
		}
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) {
			rotate = 1;
			GetComponent<ringo::SpriteComponent>()->m_texture = GET_RESOURCE(ringo::Texture, "KirbyD.png", ringo::g_renderer);
		}
		//transform.rotation += rotate * turnRate * ringo::g_time.GetDeltaTime();
		m_physicsComponent->ApplyTorque(rotate * turnRate);

		//forward/backwards motion
		float thrust = 0.0f;
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) {
			thrust = 1.0f;
			GetComponent<ringo::SpriteComponent>()->m_texture = GET_RESOURCE(ringo::Texture, "KirbyW.png", ringo::g_renderer);
		}
		ringo::vec2 forward = ringo::vec2{ 0, -1 }.Rotate(transform.rotation);

		m_physicsComponent->ApplyForce(forward * speed * thrust);

		transform.position.x = ringo::Wrap(transform.position.x, static_cast<float>(ringo::g_renderer.GetWidth()));
		transform.position.y = ringo::Wrap(transform.position.y, static_cast<float>(ringo::g_renderer.GetHeight()));

		//fire weapon
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
			!ringo::g_inputSystem.GetPrevKeyDown(SDL_SCANCODE_SPACE)) {

			auto weapon = INSTANTIATE(Weapon, "Rocket");
			weapon->transform = { transform.position, transform.rotation + ringo::DegreesToRadians(10.0f), 1 };
			weapon->Initialize();
			m_scene->Add(std::move(weapon));

			weapon = INSTANTIATE(Weapon, "Rocket");
			weapon->transform = { transform.position, transform.rotation - ringo::DegreesToRadians(10.0f), 1 };
			weapon->Initialize();
			m_scene->Add(std::move(weapon));
		}

		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) ringo::g_time.SetTimeScale(0.5f);
		else ringo::g_time.SetTimeScale(1.0f);
	}

	void Player::OnCollision(Actor* other)
	{
		//change to EnemyBullet?
		if (other->tag == "Enemy") {
			destroyed = true;

			ringo::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
		}
		//if player dead, go to PlayerDeadStart
	}

	void Player::Read(const json_t& value) {
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, turnRate);
	}
}