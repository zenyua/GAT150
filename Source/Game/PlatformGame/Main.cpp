#include "PlatformGame.h"
#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Input/Inputsystem.h"
#include "Audio/Audiosystem.h"
#include "Framework/Framework.h"
#include "Physics/PhysicsSystem.h"

#include <iostream>
#include <vector>
#include <thread>
#include <cassert>
#include <array>
#include <map>
#include <functional>

using namespace std;
using vec2 = ringo::Vector2;

int main(int argc, char* argv[]) {
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

	//set up physics
	ringo::PhysicsSystem::Instance().Initialize();

	//set up renderer
	ringo::g_renderer.Initialize();
	ringo::g_renderer.CreateWindow("csc196", 1920, 1080);

	//set up game
	std::unique_ptr<PlatformGame> game = std::make_unique<PlatformGame>();
	game->Initialize();

	//set up input
	ringo::g_inputSystem.Initialize();

	bool quit = false;
	while (!quit) {
		//update engine
		ringo::g_time.Tick();
		ringo::g_inputSystem.Update();
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}
		//move the particlesystem update to here? that's what maple has
		ringo::PhysicsSystem::Instance().Update(ringo::g_time.GetDeltaTime());

		//update game
		game->Update(ringo::g_time.GetDeltaTime());

		//draw game
		ringo::g_renderer.SetColor(255, 255, 255, 0);
		ringo::g_renderer.BeginFrame();
		ringo::g_renderer.SetColor(1, 1, 1, 255);
		game->Draw(ringo::g_renderer);
		//maple has particlesystem draw here

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
