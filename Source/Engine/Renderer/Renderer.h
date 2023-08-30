#pragma once
#include "Font.h"
#include "Model.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "Text.h"
#include "Texture.h"

#include "SDL2-2.28.0/include/SDL.h"
#include <string>

namespace ringo {
	class Renderer {
	public:
		Renderer() = default;
		~Renderer() = default;

		bool Initialize();
		void Shutdown();

		void CreateWindow(const std::string& title, int width, int height);
		void BeginFrame();
		void EndFrame();

		void SetColor(int r, int g, int b, int a);
		void DrawLine(int x1, int y1, int x2, int y2);
		void DrawLine(float x1, float y1, float x2, float y2);
		friend class Text;

		int GetWidth() const { return m_width; }
		int GetHeight() const { return m_height; }

		friend class Texture;

		void DrawTexture(class Texture* texture, float x, float y, float angle = 0.0f);
		void DrawTexture(class Texture* texture, const Transform& transform);
		void DrawTexture(class Texture* texture, const Rect& source, const Transform& transform);
		void DrawTexture(class Texture* texture, const Rect& source, const Transform& transform, const vec2& origin, bool flipH);

	private:
		int m_width = 0;
		int m_height = 0;

		SDL_Renderer* m_renderer{ nullptr };
		SDL_Window* m_window{ nullptr };
	};

	extern Renderer g_renderer;
}