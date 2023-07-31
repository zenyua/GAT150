#include "Renderer.h"
#include "SDL2-2.28.0/include/SDL_ttf.h"

namespace ringo {
	Renderer g_renderer;
	//SDL_Renderer* renderer{ nullptr };
	//SDL_Window* window{ nullptr };
	bool Renderer::Initialize()
	{
		SDL_Init(SDL_INIT_VIDEO);
		TTF_Init();

		return true;
	}
	void Renderer::Shutdown()
	{
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		TTF_Quit();
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
}