#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"
#include "Framework/Resource/ResourceManager.h"

namespace ringo {

	CLASS_DEFINITION(SpriteComponent)

	bool SpriteComponent::Initialize()
	{
		if(!textureName.empty()) m_texture = GET_RESOURCE(Texture, textureName, g_renderer);

		return true;
	}

	void SpriteComponent::Update(float dt)
	{

	}
	void SpriteComponent::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), m_owner->transform.position.x, m_owner->transform.position.y, ringo::RadiansToDegrees(m_owner->transform.rotation));
	}

	void SpriteComponent::Read(const json_t& value) {
		READ_DATA(value, textureName);
	}
}

