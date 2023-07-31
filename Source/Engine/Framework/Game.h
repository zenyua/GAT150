#pragma once
#include <memory>
#include "Scene.h"

namespace ringo {
	class Scene;
	class Renderer;

	class Game {
	public:
		Game() = default;
		virtual ~Game() = default;

		virtual bool Initialize() = 0;
		virtual void Shutdown() = 0;

		virtual void Update(float dt) = 0;
		virtual void Draw(Renderer& renderer) = 0;

		int GetScore() const { return m_score; }
		void AddPoints(int points) { m_score += points; }

		int GetLives() const { return m_lives; }
		void SetLives(int lives) { m_lives = lives; }

		void AddMoney(int money) { m_money += money; }
	protected:
		std::unique_ptr<Scene> m_scene;

		int m_money = 0;
		int m_score = 0;
		int m_lives = 0;
	};
}