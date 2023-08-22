#pragma once
#include "Framework/Singleton.h"
#include "box2d/include/box2d/b2_world.h"
#include <memory>

namespace ringo
{
	class PhysicsSystem : public Singleton<PhysicsSystem>
	{
	public:
		bool Initialize();
		void Update(float dt);

		friend class Singleton<PhysicsSystem>;
	private:
		PhysicsSystem();
	private:
		std::unique_ptr<b2World> m_world;
	};
}