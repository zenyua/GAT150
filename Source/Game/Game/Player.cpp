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
//#include <Framework/Components/EnginePhysicsComponent.h>

bool Player::Initialize() {
	Actor::Initialize();

	//cache off
	m_physicsComponent = GetComponent<ringo::PhysicsComponent>();
	auto collisionComponent = GetComponent<ringo::CollisionComponent>();
	if (collisionComponent) {
		auto renderComponent = GetComponent<ringo::RenderComponent>();
		if (renderComponent) {
			float scale = m_transform.scale;
			collisionComponent->m_radius = renderComponent->GetRadius() * scale * 0.75f;
		}
	}

	return true;
}

void Player::Update(float dt)
{
	Actor::Update(dt);

	//rotate ship
	float rotate = 0;
	if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * ringo::g_time.GetDeltaTime();

	//forward/backwards motion
	float thrust = 0.0f;
	if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) {
		thrust = 1.0f;
	}

	ringo::vec2 forward = ringo::vec2{ 0, -1 }.Rotate(m_transform.rotation);

	m_physicsComponent->ApplyForce(forward * m_speed * thrust);

	m_transform.position.x = ringo::Wrap(m_transform.position.x, static_cast<float>(ringo::g_renderer.GetWidth()));
	m_transform.position.y = ringo::Wrap(m_transform.position.y, static_cast<float>(ringo::g_renderer.GetHeight()));

	//fire weapon
	if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
		!ringo::g_inputSystem.GetPrevKeyDown(SDL_SCANCODE_SPACE)) {
		//ringo::Transform mousePosition;
		//mousePosition.position = ringo::g_inputSystem.GetMousePosition();
		//ringo::Transform tempPosition = m_transform;
		//m_transform.position.Normalize();
		//mousePosition.position.Normalize();
		//float angle = ringo::vec2::Angle(m_transform.position, mousePosition.position);
		////float angle = ringo::vec2::SignedAngle(mousePosition.position,m_transform.position);
		//angle = ringo::RadiansToDegrees(angle);
		//m_transform = tempPosition;
		
		//create weapon
		ringo::Transform transform1{m_transform.position, m_transform.rotation, 1};
		//std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(40.0f, transform1, m_model);
		// ^ line was changed to next line
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(40.0f, transform1); //removed , m_model
		weapon->m_tag = "Weapon";

		//maple had to include texture, but i didn't? also resourcemanager
		std::unique_ptr<ringo::SpriteComponent> component = std::make_unique<ringo::SpriteComponent>();
		component->m_texture = ringo::g_resources.Get<ringo::Texture>("ship.png", ringo::g_renderer);
		weapon->AddComponent(std::move(component));

		auto collisionComponent = std::make_unique<ringo::CircleCollisionComponent>();
		collisionComponent->m_radius = 30.0f;
		weapon->AddComponent(std::move(collisionComponent));

		m_scene->Add(std::move(weapon));

		ringo::Transform transform2{m_transform.position, m_transform.rotation - ringo::DegreesToRadians(-10), 1};
		weapon = std::make_unique<Weapon>(40.0f, transform2); //removed , m_model
		weapon->m_tag = "Weapon";

		component = std::make_unique<ringo::SpriteComponent>();
		component->m_texture = ringo::g_resources.Get<ringo::Texture>("ship.png", ringo::g_renderer);
		weapon->AddComponent(std::move(component));

		collisionComponent = std::make_unique<ringo::CircleCollisionComponent>();
		collisionComponent->m_radius = 30.0f;
		weapon->AddComponent(std::move(collisionComponent));

		m_scene->Add(std::move(weapon));
	}

	if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) ringo::g_time.SetTimeScale(0.5f);
	else ringo::g_time.SetTimeScale(1.0f);
}

void Player::OnCollision(Actor* other)
{
	//change to EnemyBullet?
	if (other->m_tag == "Enemy") {
		m_destroyed = true;
		m_game->m_state = Mewmont::eState::PlayerDeadStart;
		int lives = m_game->GetLives();
		lives--;
		m_game->SetLives(lives);
	}
	//if player dead, go to PlayerDeadStart
}

