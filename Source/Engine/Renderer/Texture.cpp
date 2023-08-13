#include "Texture.h"
#include "Renderer.h"
#include "SDL2-2.28.0/include/SDL_image.h"
#include "Model.h"

namespace ringo {
	Texture::~Texture() {
		if (m_texture) SDL_DestroyTexture(m_texture);
	}

	//removed this from .h cuz maple didn't have it. do we wanna keep it?
	//bool Texture::Create(Renderer& renderer, const std::string& filename) {
	//	SDL_Surface* surface = IMG_Load(filename.c_str());
	//	if (!surface)
	//	{
	//		// LOG_WARNING
	//		return false;
	//	}
	//	m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
	//	SDL_FreeSurface(surface);
	//	if (!m_texture)
	//	{
	//		// LOG_WARNING
	//		return false;
	//	}
	//	return true;
	//}

	bool Texture::Create(std::string filename, ...) {
		va_list args;

		va_start(args, filename);

		Renderer& renderer = va_arg(args, Renderer);

		va_end(args);

		return Load(filename, renderer);
	}

	bool Texture::Load(std::string filename, Renderer& renderer)
	{
		SDL_Surface* surface = IMG_Load(filename.c_str());
		if (!surface)
		{
			// LOG_WARNING
			return false;
		}
		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		SDL_FreeSurface(surface);
		if (!m_texture)
		{
			// LOG_WARNING
			return false;
		}
		return true;
	}

	vec2 Texture::GetSize()
	{
		// ASSERT texture is not null
		SDL_Point point;
		// https://wiki.libsdl.org/SDL2/SDL_QueryTexture
		//<get point.x and point.y, use link above>
		SDL_QueryTexture(this->m_texture, NULL, NULL, &point.x, &point.y);
		return vec2{ point.x, point.y };
	}

	
}