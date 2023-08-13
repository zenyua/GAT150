#pragma once
#include "Framework/Object.h"

namespace ringo {
	class Component : public Object {
	public:
		virtual void Update(float dt) = 0;

		friend class Actor;

		Actor* GetOwner() { return m_owner; }

	public:
		class Actor* m_owner = nullptr;
	};
}