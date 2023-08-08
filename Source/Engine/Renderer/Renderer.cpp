#include "Renderer.h"
#include "SDL2-2.28.0/include/SDL_ttf.h"
#include "SDL2-2.28.0/include/SDL_image.h"
#include "Texture.h"

namespace ringo {
	Renderer g_renderer;
	bool Renderer::Initialize()
	{
		SDL_Init(SDL_INIT_VIDEO);
		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
		TTF_Init();

		return true;
	}
	void Renderer::Shutdown()
	{
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		TTF_Quit();
		IMG_Quit();
	}
	void Renderer::CreateWindow(const std::string& title, int width, int height)
	{
		m_width = width;
		m_height = height;
		m_window = SDL_CreateWindow(title.c_str(), 100, 100, width,
			height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);//changed?

		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);//changed?
	}
	void Renderer::BeginFrame()
	{
		//try using renderer instead of m_renderer?
		SDL_RenderClear(m_renderer);
	}
	void Renderer::EndFrame()
	{
		SDL_RenderPresent(m_renderer);
	}
	void Renderer::SetColor(int r, int g, int b, int a)
	{
		SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
	}
	void Renderer::DrawLine(int x1, int y1, int x2, int y2)
	{
		SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
	}
	void Renderer::DrawLine(float x1, float y1, float x2, float y2)
	{
		SDL_RenderDrawLine(m_renderer, static_cast<int>(x1), static_cast<int>(y1), static_cast<int>(x2), static_cast<int>(y2));
	}
	void Renderer::DrawTexture(Texture* texture, float x, float y, float angle)
	{
		vec2 size = texture->GetSize();
		SDL_Rect dest;
		dest.x = (int)(x - (size.x + 0.5f));
		dest.y = (int)(y - (size.y + 0.5f));
		dest.w = (int)texture->GetSize().x;
		dest.h = (int)texture->GetSize().y;

		SDL_RenderCopyEx(m_renderer,texture->m_texture,NULL,&dest,angle,NULL,SDL_FLIP_NONE);
	}
}