#pragma once
#include "Core/Core.h"
#include "Renderer.h"

namespace ringo {
	struct ParticleData {
		vec2 position;
		vec2 prevPosition;
		vec2 velocity;
		float damping = 0;
		Color color{ 1,1,1,1 };
		float lifetimer = 0;
		float lifetime = 0;
	};
	class Particle
	{
	public:
		Particle() = default;
		void Initialize(const ParticleData& data)
		{
			m_data = data;
			m_isActive = true;
		}
		void Update(float dt);
		void Draw(Renderer& renderer);
		friend class ParticleSystem;
	private:
		ParticleData m_data;
		bool m_isActive = false;
	};
	

}