#include "Player.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Weapon.h"
#include "Framework/Scene.h"
#include "Core/MathUtils.h"

void Player::Update(float dt)
{
	Actor::Update(dt);

	//rotate ship
	float rotate = 0;
	if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * ringo::g_time.GetDeltaTime();

	m_damping -= 0.01;

	//forward/backwards motion
	float thrust = 0;
	if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) {
		thrust = 1;
		m_damping += 0.05;
	}
	if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_S)) {
		thrust = -1;
		m_damping += 0.05;
	}
	m_damping = ringo::Clamp(m_damping, 0.1f, 1.0f);

	ringo::vec2 forward = ringo::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	AddForce((forward * m_speed * thrust));	
	m_velocity *= m_damping;

	/*ringo::vec2 direction{0, 0};
	if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
	if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
	if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
	if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;
	direction = direction * m_speed * ringo::g_time.GetDeltaTime();
	m_transform.position = m_transform.position + direction;*/

	m_transform.position.x = ringo::Wrap(m_transform.position.x, (float)ringo::g_renderer.GetWidth());
	m_transform.position.y = ringo::Wrap(m_transform.position.y, (float)ringo::g_renderer.GetHeight());

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
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(40, transform1, m_model);
		weapon->m_tag = "Weapon";
		m_scene->Add(std::move(weapon));

		ringo::Transform transform2{m_transform.position, m_transform.rotation - ringo::DegreesToRadians(-10), 1};
		weapon = std::make_unique<Weapon>(40, transform2, m_model);
		weapon->m_tag = "Weapon";
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

