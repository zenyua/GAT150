#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"
namespace ringo{
	CLASS_DEFINITION(Weapon);

	bool Weapon::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<PhysicsComponent>();

		auto collisionComponent = GetComponent<CollisionComponent>();
		if (collisionComponent) {
			
		}

		return true;
	}

	void Weapon::Update(float dt)
	{
		Actor::Update(dt);

		ringo::vec2 forward = ringo::vec2{ 0, -1 }.Rotate(transform.rotation);
		//should the velocity be in the initialize instead of update? it's just a design question
		m_physicsComponent->SetVelocity(forward * speed);

		transform.position.x = ringo::Wrap(transform.position.x, (float)ringo::g_renderer.GetWidth());
		transform.position.y = ringo::Wrap(transform.position.y, (float)ringo::g_renderer.GetHeight());
	}

	void Weapon::OnCollisionEnter(Actor* other)
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