#pragma once
#include "Framework/Game.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"
#include "Renderer/Model.h"

#include "Framework/Event/EventManager.h"

#include <array>

class PlatformGame : public ringo::Game, ringo::IEventListener {
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

	//void SetState(eState state){m_state = }
	void OnAddPoints(const ringo::Event& event);
	void OnPlayerDead(const ringo::Event& event);

	eState m_state = eState::Title;
private:
	float m_spawnTimer = 0;
	float m_spawnTime = 60;

	float m_stateTimer = 0;
	float m_gameTimer = 0;

	std::array<int, 7> m_scores;
	std::array<std::unique_ptr<ringo::Text>, 7> m_scoresTexts;

	std::shared_ptr<ringo::Model> m_tower = std::make_shared<ringo::Model>();
	std::shared_ptr<ringo::Model> m_heart = std::make_shared<ringo::Model>();

	ringo::Transform transformH3;
	ringo::Transform transformH2;
	ringo::Transform transformH1;
};