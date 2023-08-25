#include "Text.h"
#include "Font.h"
#include "Renderer.h"
#include "Core/Math/Matrix33.h"
#include <SDL2-2.28.0/include/SDL_ttf.h>

namespace ringo {
	Text::~Text() {
		if (m_texture) SDL_DestroyTexture(m_texture);
	}
	
	void Text::Create(Renderer& renderer, const std::string& text, const Color& color) {
		//SDL_Color c{ Color::ToInt(color.r),Color::ToInt(color.g),Color::ToInt(color.b)};
		//probably shouldn't be commented out but idk how to fix it :<
		//if (m_texture != nullptr) SDL_DestroyTexture(m_texture);

		SDL_Color c{ 1,1,1 };
		SDL_Surface* surface = TTF_RenderText_Solid(m_font->m_ttfFont, text.c_str(), c);
		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		SDL_FreeSurface(surface);
	}

	void Text::Draw(Renderer& renderer, int x, int y) {
		int width, height;
		SDL_QueryTexture(m_texture, nullptr, nullptr, &width, &height);

		SDL_Rect rect{ x, y, width, height };
		SDL_RenderCopy(renderer.m_renderer, m_texture, NULL, &rect);
	}
	void Text::Draw(Renderer& renderer, const Transform& transform)
	{
		int width, height;
		SDL_QueryTexture(m_texture, nullptr, nullptr, &width, &height);

		mat3 mx = transform.GetMatrix();
		vec2 position = mx.GetTranslation();
		vec2 size = vec2{ width, height } * mx.GetScale();

		SDL_Rect dest;
		dest.x = static_cast<int>(position.x - (size.x * 0.5f));
		dest.y = static_cast<int>(position.y - (size.y * 0.5f));
		dest.w = static_cast<int>(size.x);
		dest.h = static_cast<int>(size.y);
		SDL_RenderCopyEx(renderer.m_renderer, m_texture, nullptr, &dest, RadiansToDegrees(mx.GetRotation()), nullptr, SDL_FLIP_NONE);
	}
}