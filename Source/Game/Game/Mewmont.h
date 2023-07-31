#pragma once
#include "Framework/Game.h"
#include <Renderer/Font.h>
#include <Renderer/Text.h>
#include "Renderer/Model.h"
#include <array>

class Mewmont : public ringo::Game {
public:

	enum class eState {
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDeadStart,
		PlayerDead,
		GameOverStart,
		GameOver
	};
public:
	virtual bool Initialize() override;
	virtual void Shutdown() override;

	virtual void Update(float dt) override;
	virtual void Draw(ringo::Renderer& renderer) override;

	eState m_state = eState::Title;
private:
	float m_spawnTimer = 0;
	float m_spawnTime = 30;

	float m_stateTimer = 0;
	float m_gameTimer = 0;

	std::array<int, 7> m_scores;
	std::array<std::unique_ptr<ringo::Text>, 7> m_scoresTexts;
	
	std::shared_ptr<ringo::Model> m_tower = std::make_shared<ringo::Model>();
	std::shared_ptr<ringo::Model> m_heart = std::make_shared<ringo::Model>();

	ringo::Transform transformH3;
	ringo::Transform transformH2;
	ringo::Transform transformH1;

	//std::unique_ptr<ringo::Model> m_player;

	std::shared_ptr<ringo::Font> m_font;
	std::unique_ptr<ringo::Text> m_scoreText;
	std::unique_ptr<ringo::Text> m_titleText;
	std::unique_ptr<ringo::Text> m_scoreTitleText;
	std::unique_ptr<ringo::Text> m_gameOverText;
	std::unique_ptr<ringo::Text> m_moneyText;
};