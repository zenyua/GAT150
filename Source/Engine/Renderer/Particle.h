#pragma once
#include "Core/Core.h"

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
		void Draw(class Renderer& renderer); //can't use renderer's methods here cuz it doesn't know what it is. class just says that it exists
		friend class ParticleSystem;
	private:
		ParticleData m_data;
		bool m_isActive = false;
	};
	

}