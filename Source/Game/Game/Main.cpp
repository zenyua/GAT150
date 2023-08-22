#include "Core/Core.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

#include "Input/Inputsystem.h"

#include "Audio/Audiosystem.h"

#include "Mewmont.h"

#include <iostream>
#include <vector>
#include <cassert>
#include <array>
#include <map>

using vec2 = ringo::Vector2;

int main(int argc, char* argv[]) {
	//maple removed these, it should work without them cuz we're doing this elsewhere
	//ringo::Factory::Instance().Register<ringo::SpriteComponent>("SpriteComponent");
	//ringo::Factory::Instance().Register<ringo::CircleCollisionComponent>("CircleCollisionComponent");

	INFO_LOG("testmsg")

	//set up memory
	ringo::MemoryTracker::Initialize();
	ringo::MemoryTracker::DisplayInfo();

	//set up random
	ringo::seedRandom((unsigned int)time(nullptr));

	//set file path
	ringo::setFilePath("assets");

	//set up audio
	ringo::g_audioSystem.Initialize();
	ringo::g_audioSystem.AddAudio("meow", "meow.wav");
	ringo::g_audioSystem.AddAudio("laser", "laser.wav");

	//set up renderer
	ringo::g_renderer.Initialize();
	ringo::g_renderer.CreateWindow("csc196", 1920, 1080);

	//set up game
	std::unique_ptr<Mewmont> game = std::make_unique<Mewmont>();
	game->Initialize();

	//set up input
	ringo::g_inputSystem.Initialize();

	rapidjson::Document document;
	ringo::Json::Load("json.txt", document);

	std::string str;
	ringo::Json::Read(document, "string", str);
	std::cout << str << std::endl;

	bool b;
	ringo::Json::Read(document, "boolean", b);
	std::cout << b << std::endl;

	int i1;
	ringo::Json::Read(document, "integer1", i1);
	std::cout << i1 << std::endl;

	int i2;
	ringo::Json::Read(document, "integer2", i2);
	std::cout << i2 << std::endl;

	float f;
	ringo::Json::Read(document, "float", f);
	std::cout << f << std::endl;

	ringo::vec2 v2;
	ringo::Json::Read(document, "vector2", v2, true);
	std::cout << v2 << std::endl;

	//make a texture
	//ringo::res_t<ringo::Texture> texture = ringo::g_resources.Get<ringo::Texture>("KirbyB.png", ringo::g_renderer);

	bool quit = false;
	while (!quit) {
		//renderer setup
		ringo::g_renderer.SetColor(255, 255, 255, 0);
		ringo::g_renderer.BeginFrame();
		ringo::g_renderer.SetColor(1, 1, 1, 255);

		//draw a texture
		//ringo::g_renderer.DrawTexture(texture.get(), 200.0f, 200.0f, 0.0f);

		//time stuff
		ringo::g_time.Tick();

		//inputSystem stuff
		ringo::g_inputSystem.Update();

		//check if ending game
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}

		//update game
		game->Update(ringo::g_time.GetDeltaTime());
		game->Draw(ringo::g_renderer);

		//audio system stuff
		ringo::g_audioSystem.Update();

		//SDL_Event loop
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return 0;
			}
		}

		ringo::g_renderer.EndFrame();
	};

	ringo::MemoryTracker::DisplayInfo();

	return 0;
}
