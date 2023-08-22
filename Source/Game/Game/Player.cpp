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
	float rotate = 0;
	if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) {
		rotate = -1;
		GetComponent<ringo::SpriteComponent>()->m_texture = GET_RESOURCE(ringo::Texture, "KirbyA.png", ringo::g_renderer);
	}
	if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) {
		rotate = 1;
		GetComponent<ringo::SpriteComponent>()->m_texture = GET_RESOURCE(ringo::Texture, "KirbyD.png", ringo::g_renderer);
	}
	transform.rotation += rotate * m_turnRate * ringo::g_time.GetDeltaTime();

	//ringo::SpriteComponent* sc = GetComponent<ringo::SpriteComponent>();
	//sc->m_texture = ringo::g_resources.Get<ringo::Texture>("KirbyW.png", ringo::g_renderer);
	

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
	//if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
	//	!ringo::g_inputSystem.GetPrevKeyDown(SDL_SCANCODE_SPACE)) {
	auto weapon = INSTANTIATE(Weapon, "Rocket");
	//weapon->transform = {};
	weapon->Initialize();
	m_scene->Add(std::move(weapon));
	//	//ringo::Transform mousePosition;
	//	//mousePosition.position = ringo::g_inputSystem.GetMousePosition();
	//	//ringo::Transform tempPosition = transform;
	//	//transform.position.Normalize();
	//	//mousePosition.position.Normalize();
	//	//float angle = ringo::vec2::Angle(transform.position, mousePosition.position);
	//	////float angle = ringo::vec2::SignedAngle(mousePosition.position,transform.position);
	//	//angle = ringo::RadiansToDegrees(angle);
	//	//transform = tempPosition;
	//	
	//	//create weapon
	//	ringo::Transform transform1{transform.position, transform.rotation, 1};
	//	//std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(40.0f, transform1, m_model);
	//	// ^ line was changed to next line
	//	std::unique_ptr<ringo::Weapon> weapon = std::make_unique<ringo::Weapon>(40.0f, transform1); //removed , m_model
	//	//weapon->tag = "Weapon";

	//	//maple had to include texture, but i didn't? also resourcemanager
	//	std::unique_ptr<ringo::SpriteComponent> component = std::make_unique<ringo::SpriteComponent>();
	//	component->m_texture = GET_RESOURCE(ringo::Texture, "KirbyL.png", ringo::g_renderer);
	//	weapon->AddComponent(std::move(component));

	//	auto collisionComponent = std::make_unique<ringo::CircleCollisionComponent>();
	//	collisionComponent->m_radius = 30.0f;
	//	weapon->AddComponent(std::move(collisionComponent));

	//	m_scene->Add(std::move(weapon));

	//	ringo::Transform transform2{transform.position, transform.rotation - ringo::DegreesToRadians(-10), 1};
	//	weapon = std::make_unique<Weapon>(40.0f, transform2); //removed , m_model
	//	weapon->tag = "Weapon";

	//	component = std::make_unique<ringo::SpriteComponent>();
	//	component->m_texture = GET_RESOURCE(ringo::Texture, "KirbyL.png", ringo::g_renderer);
	//	weapon->AddComponent(std::move(component));

	//	collisionComponent = std::make_unique<ringo::CircleCollisionComponent>();
	//	collisionComponent->m_radius = 30.0f;
	//	weapon->AddComponent(std::move(collisionComponent));

	//	m_scene->Add(std::move(weapon));
	//}

	if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) ringo::g_time.SetTimeScale(0.5f);
	else ringo::g_time.SetTimeScale(1.0f);
}

void Player::OnCollision(Actor* other)
{
	//change to EnemyBullet?
	if (other->tag == "Enemy") {
		destroyed = true;
		m_game->m_state = Mewmont::eState::PlayerDeadStart;
		int lives = m_game->GetLives();
		lives--;
		m_game->SetLives(lives);
	}
	//if player dead, go to PlayerDeadStart
}

