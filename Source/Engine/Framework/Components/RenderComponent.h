#pragma once
#include "Component.h"
#include "Renderer/Renderer.h"

namespace ringo {
	class RenderComponent : public Component {
	public:
		//try ringo:: instead of include?
		virtual void Draw(Renderer& renderer) = 0;
	};
}