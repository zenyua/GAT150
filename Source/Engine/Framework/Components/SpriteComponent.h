#pragma once
#include "RenderComponent.h"
#include "Renderer/Texture.h"

namespace ringo {
	class SpriteComponent : public RenderComponent {
	public:
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;

		virtual float GetRadius() override { return m_texture->GetSize().Length() * 0.5f; }

	public:
		res_t<Texture> m_texture;
	};
}