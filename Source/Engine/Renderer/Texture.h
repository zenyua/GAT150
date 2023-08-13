#pragma once
#include "Core/Math/Vector2.h"
#include "Framework/Resource/Resource.h"
#include "Text.h" //assignment didn't have this?...

struct SDL_Texuture;

namespace ringo {
	class Texture : public Resource{
	public:
		Texture() = default;
		~Texture();

		//i dont think maple has this
		//bool Create(class Renderer& renderer, const std::string& filename);
		vec2 GetSize();

		friend class Renderer;

		//Maple code
		virtual bool Create(std::string filename, ...) override;
		bool Load(std::string filename, class Renderer& renderer); //was create

	private:
		SDL_Texture* m_texture = nullptr;
	};

}