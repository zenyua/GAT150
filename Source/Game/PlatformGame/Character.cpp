#include "Character.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

namespace ringo {
	CLASS_DEFINITION(Character)

	bool Character::Initialize() {
		Actor::Initialize();

		//cache off
		m_physicsComponent = GetComponent<PhysicsComponent>();
		m_spriteAnimComponent = GetComponent<SpriteAnimRenderComponent>();

		return true;
	}

	void Character::Update(float dt)
	{
		Actor::Update(dt);

		float dir = 0;
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) {
			dir = -1;
		}
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) {
			dir = 1;
		}

		ringo::vec2 forward = ringo::vec2{ 1, 0 };
		bool onGround = (groundCount > 0);
		float uhh = 1.0f;

		if (!onGround) {
			uhh = 0.3f;
		}

		m_physicsComponent->ApplyForce(forward * speed * dir * uhh);

		//jump

		if (onGround && ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !ringo::g_inputSystem.GetPrevKeyDown(SDL_SCANCODE_SPACE)) {
			ringo::vec2 up = ringo::vec2{ 0,-1 };
			m_physicsComponent->SetVelocity(up * jump);
		}

		//animation
		vec2 velocity = m_physicsComponent->velocity;
		//check if moving
		if (std::fabs(velocity.x) > 0.2f) {
			if(dir != 0) m_spriteAnimComponent->flipH = (dir < 0);
			m_spriteAnimComponent->SetSequence("walkR");
		}
		else {
			m_spriteAnimComponent->SetSequence("idle");
		}
	}

	void Character::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Enemy") {
			//destroyed = true;

			EVENT_DISPATCH("OnPlayerDead", 0);
		}
		if (other->tag == "Ground") groundCount++;
		//if Character dead, go to CharacterDeadStart
		if (other->tag == "Coin") {
			EVENT_DISPATCH("OnGetCoin", true);
		}
		if (other->tag == "Door") {
			EVENT_DISPATCH("StartLvl2", 0);
		}
	}

	void Character::OnCollisionExit(Actor* other)
	{
		if (other->tag == "Ground") groundCount--;
	}

	void Character::Read(const json_t& value) {
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, jump);
	}
}