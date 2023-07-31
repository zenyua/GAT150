#include "Core/Core.h"

#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"

#include "Input/Inputsystem.h"

#include "Audio/Audiosystem.h"

#include "Mewmont.h"

#include <iostream>
#include <vector>

using vec2 = ringo::Vector2;

int main(int argc, char* argv[]) {
	//debug stuff
#ifdef _DEBUG
	std::cout << "debug mode\n";
#endif _DEBUG


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

	bool quit = false;
	while (!quit) {
		//renderer setup
		ringo::g_renderer.SetColor(255, 255, 255, 0);
		ringo::g_renderer.BeginFrame();
		ringo::g_renderer.SetColor(1, 1, 1, 255);

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



//if (ringo::g_inputSystem.GetMouseButtonDown(0) && !ringo::g_inputSystem.GetMousePrevButtonDown(0)) {
//	std::cout << "left down.\n";
//	std::cout << "x: " << ringo::g_inputSystem.GetMousePosition().x;
//	std::cout << " y: " << ringo::g_inputSystem.GetMousePosition().y;
//	std::cout << "\n";
//}
//if (ringo::g_inputSystem.GetMouseButtonDown(1) && !ringo::g_inputSystem.GetMousePrevButtonDown(1)) {
//	std::cout << "middle down.\n";
//	std::cout << "x: " << ringo::g_inputSystem.GetMousePosition().x;
//	std::cout << " y: " << ringo::g_inputSystem.GetMousePosition().y;
//	std::cout << "\n";
//}
//if (ringo::g_inputSystem.GetMouseButtonDown(2) && !ringo::g_inputSystem.GetMousePrevButtonDown(2)) {
//	std::cout << "right down.\n";
//	std::cout << "x: " << ringo::g_inputSystem.GetMousePosition().x;
//	std::cout << " y: " << ringo::g_inputSystem.GetMousePosition().y;
//	std::cout << "\n";
//}

//player movement stuff
		/*ringo::vec2 direction{0, 0};
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;
		direction = direction * speed * ringo::g_time.GetDeltaTime();
		transform.position = transform.position + direction;*/