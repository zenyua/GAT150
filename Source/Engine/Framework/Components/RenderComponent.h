#pragma once
#include "Component.h"

namespace ringo {
	class RenderComponent : public Component {
	public:
		virtual void Draw(class Renderer& renderer) = 0;
		virtual float GetRadius() { return 0; }
	};
}