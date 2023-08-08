#include "Core/Core.h"

#include "Renderer/Renderer.h"
#include "Renderer/Texture.h"

#include "Input/Inputsystem.h"

#include "Audio/Audiosystem.h"

#include "Mewmont.h"

#include <iostream>
#include <vector>
#include <cassert>
#include <array>
#include <map>
#include <Framework/Resource/ResourceManager.h>

template <typename T>
void print(const std::string& s, const T& container)
{
	std::cout << s << std::endl;
		for (auto element : container)
		{
			std::cout << element << " ";
		}
	std::cout << std::endl;
}

using vec2 = ringo::Vector2;

int main(int argc, char* argv[]) {

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

	//make a texture
	ringo::res_t<ringo::Texture> texture = ringo::g_resources.Get<ringo::Texture>("kirbyb.png", ringo::g_renderer);

	bool quit = false;
	while (!quit) {
		//renderer setup
		ringo::g_renderer.SetColor(255, 255, 255, 0);
		ringo::g_renderer.BeginFrame();
		ringo::g_renderer.SetColor(1, 1, 1, 255);

		//draw a texture
		ringo::g_renderer.DrawTexture(texture.get(), 200.0f, 200.0f, 0.0f);

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
