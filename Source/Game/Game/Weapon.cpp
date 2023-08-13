#include "Weapon.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

bool Weapon::Initialize()
{
	Actor::Initialize();
	auto collisionComponent = GetComponent<ringo::CollisionComponent>();
	if (collisionComponent) {
		auto renderComponent = GetComponent<ringo::RenderComponent>();
		if (renderComponent) {
			float scale = m_transform.scale;
			collisionComponent->m_radius = renderComponent->GetRadius() * scale;
		}
	}

	return true;
}

void Weapon::Update(float dt)
{
	Actor::Update(dt);
	ringo::vec2 forward = ringo::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * ringo::g_time.GetDeltaTime();
	m_transform.position.x = ringo::Wrap(m_transform.position.x, (float)ringo::g_renderer.GetWidth());
	m_transform.position.y = ringo::Wrap(m_transform.position.y, (float)ringo::g_renderer.GetHeight());
}

void Weapon::OnCollision(Actor* other)
{
	if (other->m_tag != m_tag) {
		m_destroyed = true;
	}
}
