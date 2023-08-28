#include "PlatformGame.h"

#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"

bool PlatformGame::Initialize()
{
	//set up scores
	for (int i = 0; i < m_scoresTexts.size(); i++)
	{
		m_scoresTexts[i] = std::make_unique<ringo::Text>(GET_RESOURCE(ringo::Font, "organo.ttf", 24));
	}
	for (int score : m_scores) {
		score = 0;
	}

	//set up audio
	ringo::g_audioSystem.Initialize();
	ringo::g_audioSystem.AddAudio("meow", "meow.wav");
	ringo::g_audioSystem.AddAudio("laser", "laser.wav");

	//create scene
	m_scene = std::make_unique<ringo::Scene>();
	m_scene->Load("scenes/platformscene.json");
	m_scene->Initialize();
	//Maple has this but I don't have the method for it :((
	//m_scene->SetGame(this);

	//add events
	EVENT_SUBSCRIBE("OnAddPoints", PlatformGame::OnAddPoints);
	EVENT_SUBSCRIBE("OnPlayerDead", PlatformGame::OnPlayerDead);

	return true;
}

void PlatformGame::Shutdown()
{

}

void PlatformGame::Update(float dt)
{
	switch (m_state)
	{
	case PlatformGame::eState::Title:
	{
		break;
	}
	case PlatformGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;
	case PlatformGame::eState::StartLevel:
	{

		m_state = eState::Game;
		break;
	}
	case PlatformGame::eState::Game:
	{
		ringo::g_particleSystem.Update(dt);
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !ringo::g_inputSystem.GetPrevKeyDown(SDL_SCANCODE_SPACE)) {
			ringo::g_audioSystem.PlayOneShot("laser");
		}
		
		break;
	}
	case eState::PlayerDeadStart:

		break;
	case PlatformGame::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) {
			m_state = eState::StartLevel;
		}
		break;
	case PlatformGame::eState::GameOverStart:
		//update score table
		if (m_score > m_scores[0]) {
			m_scores[0] = m_score;
			std::sort(m_scores.begin(), m_scores.end());
		}
		for (int i = 0; i < m_scoresTexts.size(); i++)
		{
			m_scoresTexts[i]->Create(ringo::g_renderer, std::to_string(m_scores[i]), { 1,1,1,1 });
		}
		m_state = eState::GameOver;
		break;
	case PlatformGame::eState::GameOver:
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) m_state = eState::Title;
		break;
	default:
		break;
	}
	m_scene->Update(dt);
}

void PlatformGame::Draw(ringo::Renderer& renderer)
{
	if (m_state == eState::Game) {
		ringo::g_particleSystem.Draw(renderer);
		switch (m_lives) {
		case 1:
			m_heart->Draw(renderer, transformH3);
			break;
		case 2:
			m_heart->Draw(renderer, transformH3);
			m_heart->Draw(renderer, transformH2);
			break;
		case 3:
			m_heart->Draw(renderer, transformH3);
			m_heart->Draw(renderer, transformH2);
			m_heart->Draw(renderer, transformH1);
			break;
		}
	}
	if (m_state == eState::GameOver) {
		for (int i = 6; i >= 0; i--)
		{
			m_scoresTexts[i]->Draw(renderer, 300, (10 - i) * 50);
		}
	}
	m_scene->Draw(renderer);
}


//OnAddPoints
void PlatformGame::OnAddPoints(const ringo::Event& event)
{
	m_score += std::get<int>(event.data);
}

void PlatformGame::OnPlayerDead(const ringo::Event& event)
{
	m_lives--;
	m_state = eState::PlayerDeadStart;
}

