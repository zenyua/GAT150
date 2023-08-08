#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"

namespace ringo {
	void SpriteComponent::Update(float dt)
	{

	}
	void ringo::SpriteComponent::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), m_owner->m_transform.position.x, m_owner->m_transform.position.y, ringo::RadiansToDegrees(m_owner->m_transform.rotation));
	}
}

