#include "Actor.h"
namespace ringo {
	void Actor::Update(float dt)
	{
		if (m_lifespan != -1) {
			m_lifespan -= dt;
			m_destroyed = m_lifespan <= 0;
		}

		m_transform.position += m_velocity * dt;
	}
	void Actor::Draw(ringo::Renderer& renderer)
	{
		m_model->Draw(renderer, m_transform);
	}
}
