#include "PlatformGame.h"

#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"

bool PlatformGame::Initialize()
{
	//set up audio
	ringo::g_audioSystem.Initialize();
	ringo::g_audioSystem.AddAudio("jump", "audio/jump.wav");
	ringo::g_audioSystem.AddAudio("test", "audio/test.wav");

	//create scene
	m_scene = std::make_unique<ringo::Scene>();
	m_scene->Load("scenes/titlescene.json");
	m_scene->Initialize();

	//add events
	EVENT_SUBSCRIBE("OnAddPoints", PlatformGame::OnAddPoints);
	EVENT_SUBSCRIBE("OnPlayerDead", PlatformGame::OnPlayerDead);
	EVENT_SUBSCRIBE("OnGetCoin", PlatformGame::OnGetCoin);
	EVENT_SUBSCRIBE("StartLvl2", PlatformGame::StartLvl2);

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
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_W) && !ringo::g_inputSystem.GetPrevKeyDown(SDL_SCANCODE_W)) {
			ringo::g_audioSystem.PlayOneShot("test");
		}
		
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !ringo::g_inputSystem.GetPrevKeyDown(SDL_SCANCODE_SPACE)) {
			m_state = eState::StartLevel2;
			//m_state = eState::StartGame;
		}
		break;
	}
	case PlatformGame::eState::StartGame:
	{
		m_scene->RemoveAll();
		m_scene->Load("scenes/platformscene.json");
		m_scene->Load("scenes/myTiles1.json");
		m_scene->Initialize();
		auto coin = INSTANTIATE(Actor, "Coin");
		coin->transform.position = { 600, 300 };
		coin->Initialize();
		m_scene->Add(std::move(coin));
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;
	}
	case PlatformGame::eState::StartLevel:
	{
		m_state = eState::Game;
		break;
	}
	case PlatformGame::eState::Game:
	{
		ringo::g_particleSystem.Update(dt);
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !ringo::g_inputSystem.GetPrevKeyDown(SDL_SCANCODE_SPACE)) {
			ringo::g_audioSystem.PlayOneShot("jump");
		}
		if (makeNewCoin) {
			auto coinn = INSTANTIATE(Actor, "Coin");
			coinn->transform.position = ringo::Vector2{ 25, 610 };
			coinn->persistent = true;
			coinn->Initialize();
			m_scene->Add(std::move(coinn));
			makeNewCoin = false;
		}
		if (makeNewDoor) {
			auto door = INSTANTIATE(Actor, "Door");
			door->transform.position = ringo::Vector2{ 100, 100 };
			door->Initialize();
			m_scene->Add(std::move(door));
			makeNewDoor = false;
		}
		break;
	}
	case eState::StartLevel2:
	{
		m_scene->RemoveAll();
		m_scene->Load("scenes/level2.json");
		m_scene->Load("scenes/myTiles2.json");
		m_scene->Initialize();
		m_state = eState::Game2;
		break;
	}
	case eState::Game2:

		break;
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

	}
	if (m_state == eState::GameOver) {

	}
	m_scene->Draw(renderer);
}


//OnAddPoints
void PlatformGame::OnAddPoints(const ringo::Event& event)
{
	//m_score += std::get<int>(event.data);
}

void PlatformGame::OnPlayerDead(const ringo::Event& event)
{
	m_lives--;
	m_state = eState::PlayerDeadStart;
}

void PlatformGame::OnGetCoin(const ringo::Event& event)
{
	auto actor = m_scene->GetActorByName("Coin");
	if (actor) {
		actor->destroyed = true;
		makeNewCoin = true;
		makeNewDoor = true;
	}
}
void PlatformGame::StartLvl2(const ringo::Event& event)
{
	m_state = eState::StartLevel2;
}
//
//void PlatformGame::OnGetItem(const ringo::Event& event, std::string itemName)
//{
//	auto actor = m_scene->GetActorByName(itemName);
//	if (actor) {
//		actor->active = false;
//	}
//}

