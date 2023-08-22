#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Framework/Resource/ResourceManager.h"

namespace ringo {

	CLASS_DEFINITION(SpriteComponent)

	bool SpriteComponent::Initialize()
	{
		if(!name.empty()) m_texture = GET_RESOURCE(Texture, name, g_renderer);

		return true;
	}

	void SpriteComponent::Update(float dt)
	{

	}
	void ringo::SpriteComponent::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), m_owner->transform.position.x, m_owner->transform.position.y, ringo::RadiansToDegrees(m_owner->transform.rotation));
	}

	void SpriteComponent::Read(const json_t& value) {

	}
}

