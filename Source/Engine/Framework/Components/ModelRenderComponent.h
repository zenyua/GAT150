#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"

namespace ringo {
	class ModelRenderComponent : public RenderComponent {
	public:
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;

		virtual float GetRadius() override { return m_model->GetRadius(); }

	public:
		res_t<Model> m_model;
	};
}