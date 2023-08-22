#include "Mewmont.h"

#include "Framework/Framework.h"

#include "Player.h"
#include "Enemy.h"
#include "Tower.h"

#include "Audio/AudioSystem.h"

#include "Input/InputSystem.h"

#include "Renderer/Renderer.h"

bool Mewmont::Initialize()
{
	//set up text
	m_titleText = std::make_unique<ringo::Text>(GET_RESOURCE(ringo::Font, "organo.ttf", 24));
	m_titleText->Create(ringo::g_renderer, "mewmont", ringo::Color{1, 1, 1, 1});
	m_scoreText = std::make_unique<ringo::Text>(GET_RESOURCE(ringo::Font, "organo.ttf", 24));
	m_scoreText->Create(ringo::g_renderer, "0", ringo::Color{1, 1, 1, 1});
	m_gameOverText = std::make_unique<ringo::Text>(GET_RESOURCE(ringo::Font, "organo.ttf", 24));
	m_gameOverText->Create(ringo::g_renderer, "Game Over", ringo::Color{1, 1, 1, 1});
	m_scoreTitleText = std::make_unique<ringo::Text>(GET_RESOURCE(ringo::Font, "organo.ttf", 24));
	m_scoreTitleText->Create(ringo::g_renderer, "High Scores", ringo::Color{1, 1, 1, 1});
	m_moneyText = std::make_unique<ringo::Text>(GET_RESOURCE(ringo::Font, "organo.ttf", 24));

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
	m_scene->Load("scene.json");
	m_scene->Initialize();

	return true;
}

void Mewmont::Shutdown()
{
}

void Mewmont::Update(float dt)
{
	switch (m_state)
	{
	case Mewmont::eState::Title:
	{
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !ringo::g_inputSystem.GetPrevKeyDown(SDL_SCANCODE_SPACE)) {
			m_state = eState::StartGame;
			auto actor = m_scene->GetActorByName("Background");
			if(actor) actor->active = false;
		}
		break;
	}
	case Mewmont::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;
	case Mewmont::eState::StartLevel:
	{
		//maple's transform is inline
		ringo::Transform transform;
		transform.position = { 500.0f, 500.0f };
		transform.scale = 1.0f;

		std::unique_ptr<Player> player = std::make_unique<Player>(2.0f,0.1f,transform,this);
		player->tag = "Player";

		//heart model
		m_heart->Load("heart.txt");
		transformH3.position = { 700, 50 };
		transformH2.position = { 650, 50 };
		transformH1.position = { 600, 50 };
		transformH3.scale = 4;
		transformH2.scale = 4;
		transformH1.scale = 4;

		//tower model
		m_tower->Load("tower.txt");

		//make player components
		//get this line fixed :)
		auto renderComponent = CREATE_CLASS(SpriteComponent);
		//ringo::Factory::Instance().Create<ringo::SpriteComponent>("SpriteComponent"); swapped for macro

		auto component = CREATE_CLASS(SpriteComponent);
		component->m_texture = GET_RESOURCE(ringo::Texture, "KirbyW.png", ringo::g_renderer);
		player->AddComponent(std::move(component));

		auto physicsComponent = CREATE_CLASS(EnginePhysicsComponent);
		physicsComponent->m_damping = 0.9f;
		player->AddComponent(std::move(physicsComponent));

		auto collisionComponent = CREATE_CLASS(CircleCollisionComponent);
		collisionComponent->m_radius = 10.0f;
		player->AddComponent(std::move(collisionComponent));

		player->Initialize();
		m_scene->Add(std::move(player));

		m_state = eState::Game;
		break;
	}
	case Mewmont::eState::Game:
	{
		ringo::g_particleSystem.Update(dt);
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime) {

			m_spawnTimer = 0;
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(1.0f, ringo::Pi, ringo::Transform{{100, 100}, ringo::randomf(ringo::TwoPi), 1});
			enemy->tag = "Enemy";
			enemy->m_game = this;

			auto spriteComponent = std::make_unique<ringo::SpriteComponent>();
			spriteComponent->m_texture = GET_RESOURCE(ringo::Texture, "Kirbo.png", ringo::g_renderer);
			enemy->AddComponent(std::move(spriteComponent));

			auto collisionComponent = std::make_unique<ringo::CircleCollisionComponent>();
			collisionComponent->m_radius = 10.0f;
			enemy->AddComponent(std::move(collisionComponent));

			enemy->Initialize();
			m_scene->Add(std::move(enemy));
		}
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !ringo::g_inputSystem.GetPrevKeyDown(SDL_SCANCODE_SPACE)) {
			ringo::g_audioSystem.PlayOneShot("laser");
		}
		/*if (ringo::g_inputSystem.GetMouseButtonDown(0) && !ringo::g_inputSystem.GetMousePrevButtonDown(0) && m_money >= 50) {
			m_money -= 50;
			ringo::Transform transform;
			transform.position = ringo::g_inputSystem.GetMousePosition();
			transform.scale = 5;
			transform.rotation = ringo::randomf(360);
			std::unique_ptr<Tower> tower = std::make_unique<Tower>(5.0f,transform);
			tower->tag = "Tower";
			tower->m_game = this;
			m_scene->Add(std::move(tower));
		}*/
		m_moneyText->Create(ringo::g_renderer, "Gold: " + std::to_string(m_money), ringo::Color{1, 1, 1, 1});
		break;
	}
	case eState::PlayerDeadStart:
		m_stateTimer = 30;
		if (m_lives <= 0) {
			m_state = eState::GameOverStart;
		}
		else m_state = eState::PlayerDead;
		ringo::g_audioSystem.PlayOneShot("meow");
		m_scene->RemoveAll();
		break;
	case Mewmont::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) {
			m_state = eState::StartLevel;
		}
		break;
	case Mewmont::eState::GameOverStart:
		//update score table
		if (m_score > m_scores[0]) {
			m_scores[0] = m_score;
			std::sort(m_scores.begin(), m_scores.end());
		}
		for (int i = 0; i < m_scoresTexts.size(); i++)
		{
			m_scoresTexts[i]->Create(ringo::g_renderer, std::to_string(m_scores[i]), {1,1,1,1});
		}
		m_scene->RemoveAll();
		m_state = eState::GameOver;
		break;
	case Mewmont::eState::GameOver:
		if(ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) m_state = eState::Title;
		break;
	default:
		break;
	}
	m_scoreText->Create(ringo::g_renderer, std::to_string(m_score), { 1,1,1,1 });
	m_scene->Update(dt);
}

void Mewmont::Draw(ringo::Renderer& renderer)
{
	if (m_state == eState::Title) {
		m_titleText->Draw(renderer, 400, 300);
	}
	if (m_state == eState::Game) {
		ringo::g_particleSystem.Draw(renderer);
		m_scoreText->Draw(renderer, 0, 0);
		m_moneyText->Draw(renderer, 1300, 20);
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
		m_gameOverText->Draw(renderer, 250, 0);
		m_scoreTitleText->Draw(renderer, 250, 50);
		for (int i = 6; i >= 0; i--)
		{
			m_scoresTexts[i]->Draw(renderer,300,(10-i)*50);
		}
	}
	m_scene->Draw(renderer);
}

