#pragma once
#include "Vector2.h"

namespace ringo {
	class Transform {
	public:
		vec2 position = { 0,0 };
		float rotation = 0;
		float scale = 1;

	public: 
		Transform() = default;
		Transform(const vec2& position, float rotation, float scale) :
			position{position},
			rotation{rotation},
			scale{ scale } {}
	};
}