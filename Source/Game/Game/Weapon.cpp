#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"
namespace ringo{
	CLASS_DEFINITION(Weapon);

	bool Weapon::Initialize()
	{
		Actor::Initialize();

		auto collisionComponent = GetComponent<ringo::CollisionComponent>();
		if (collisionComponent) {
			auto renderComponent = GetComponent<ringo::RenderComponent>();
			if (renderComponent) {
				float scale = transform.scale;
				collisionComponent->m_radius = renderComponent->GetRadius() * scale;
			}
		}

		return true;
	}

	void Weapon::Update(float dt)
	{
		Actor::Update(dt);

		ringo::vec2 forward = ringo::vec2{ 0, -1 }.Rotate(transform.rotation);
		transform.position += forward * speed * ringo::g_time.GetDeltaTime();
		transform.position.x = ringo::Wrap(transform.position.x, (float)ringo::g_renderer.GetWidth());
		transform.position.y = ringo::Wrap(transform.position.y, (float)ringo::g_renderer.GetHeight());
	}

	void Weapon::OnCollision(Actor* other)
	{
		if (other->tag != tag) {
			destroyed = true;
		}
	}

	void Weapon::Read(const json_t& value) {
		Actor::Read(value);

		READ_DATA(value, speed);
	}
}