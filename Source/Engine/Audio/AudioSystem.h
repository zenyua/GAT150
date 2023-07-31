#pragma once
#include <fmod/core/inc/fmod.hpp>
#include <string>
#include <map>

namespace ringo {
	class AudioSystem {
	public:
		AudioSystem() = default;
		~AudioSystem() = default;

		bool Initialize();
		void Shutdown();

		void Update();

		void AddAudio(const std::string& name, const std::string& filename);
		void PlayOneShot(const std::string& name);
	private:
		FMOD::System* m_fmodSystem;
		std::map<std::string, FMOD::Sound*> m_sounds;
	};

	void f();

	extern AudioSystem g_audioSystem;
}