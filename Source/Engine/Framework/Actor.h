#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"

#include <memory>

namespace ringo {
	class Actor {
	public:
		Actor() = default;
		Actor(const ringo::Transform& transform) :
			m_transform{ transform }
		{}
		Actor(const ringo::Transform& transform, std::shared_ptr<Model> model) :
			m_model{ model },
			m_transform{ transform } {}

		virtual void Update(float dt);
		virtual void Draw(ringo::Renderer& renderer);

		float GetRadius() { return (m_model) ? m_model->GetRadius() * m_transform.scale : 0; }
		virtual void OnCollision(Actor* other) {};

		void AddForce(vec2 force) { m_velocity += force; }
		void SetDamping(float damping) { m_damping = damping; }

		class Scene* m_scene = nullptr;
		friend class Scene;
		class Game* m_game = nullptr;

		ringo::Transform m_transform;
		std::string m_tag;
		float m_lifespan = -1.0f;
	protected:
		bool m_destroyed = false;

		std::shared_ptr<Model> m_model;

		vec2 m_velocity = 0;
		//slows stuff down if it's closer to 1
		float m_damping = 0;
	};
}