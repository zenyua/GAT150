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
		StartLevel2,
		Game2,
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
	void OnGetCoin(const ringo::Event& event);
	void OnGetApple(const ringo::Event& event);
	void OnGetStrawberry(const ringo::Event& event);
	void OnGetTree(const ringo::Event& event);
	void StartLvl2(const ringo::Event& event);

	eState m_state = eState::Title;
private:
	float m_spawnTimer = 0;
	float m_spawnTime = 60;

	float m_stateTimer = 0;
	float m_gameTimer = 0;

	bool makeNewCoin = false;
	bool makeNewDoor = false;
	bool getApple = false;
	bool getStrawberry = false;
};