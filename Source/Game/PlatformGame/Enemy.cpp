#include "Enemy.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "Core/Core.h"
#include <Framework/Components/SpriteAnimRenderComponent.h>
#include <Framework/Components/PhysicsComponent.h>
#include <Framework/Resource/ResourceManager.h>
#include <Framework/Components/CircleCollisionComponent.h>
#include "Character.h"

namespace ringo {
	CLASS_DEFINITION(Enemy)
		bool Enemy::Initialize() {
		Actor::Initialize();

		//cache off
		m_physicsComponent = GetComponent<PhysicsComponent>();
		m_spriteAnimComponent = GetComponent<SpriteAnimRenderComponent>();

		return true;
	}

	void Enemy::OnDestroy() {
		Actor::OnDestroy();
	}

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);

		ringo::vec2 forward = ringo::vec2{ 0,-1 }.Rotate(transform.rotation);
		Character* character = m_scene->GetActor<Character>();
		if (character) {
			vec2 direction = character->transform.position - transform.position;
			m_physicsComponent->ApplyForce(direction.Normalized() * speed);
		}


		vec2 velocity = m_physicsComponent->velocity;
		if (std::fabs(velocity.x) > 0.2f) {
			//if (dir != 0) m_spriteAnimComponent->flipH = (dir < 0);
			m_spriteAnimComponent->SetSequence("walkR");
		}
		else {
			m_spriteAnimComponent->SetSequence("idle");
		}

		//Wrap?

		/*float dir = 0;
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) {
			dir = -1;
		}
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) {
			dir = 1;
		}

		ringo::vec2 forward = ringo::vec2{ 1, 0 };
		m_physicsComponent->ApplyForce(forward * speed * dir);*/


	}

	void Enemy::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Enemy") {
			destroyed = true;

			//EVENT_DISPATCH("OnPlayerDead", 0);
		}
		if (other->tag == "Ground") groundCount++;
		//if Enemy dead, go to EnemyDeadStart
	}

	void Enemy::OnCollisionExit(Actor* other)
	{
		if (other->tag == "Ground") groundCount--;
	}

	void Enemy::Read(const json_t& value) {
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, jump);
	}
}