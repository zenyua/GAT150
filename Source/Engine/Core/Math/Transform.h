#pragma once
#include "Vector2.h"
#include "Matrix33.h"

namespace ringo {
	class Transform {
	public:
		//maple doesn't have ={0,0}; ????
		vec2 position = { 0,0 };
		float rotation = 0;
		float scale = 1;

	public:
		Transform() = default;
		Transform(const vec2& position, float rotation, float scale) :
			position{ position },
			rotation{ rotation },
			scale{ scale } {}
		mat3 GetMatrix() const { 
			mat3 ms = mat3::CreateScale(scale);
			mat3 mr = mat3::CreateRotation(rotation);
			mat3 mt = mat3::CreateTranslation(position);
			mat3 mx = mt * ms * mr;

			return mx;
		}
	};
}