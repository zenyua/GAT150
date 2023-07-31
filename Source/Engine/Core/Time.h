#pragma once
#include <chrono>

namespace ringo {
	class Time {
	private:
		using clock = std::chrono::high_resolution_clock;
		using clock_duration = clock::duration;
		using clock_rep = clock::rep;

	public:
		Time() :
			m_startTime{ clock::now() },
			m_frameTime{ clock::now() } {}
		void Tick();
		void Reset() { m_startTime = clock::now(); }

		clock_rep GetElapsedNanoseconds();
		clock_rep GetElapsedMicroseconds();
		clock_rep GetElapsedMilliseconds();
		float GetElapsedSeconds();
		float GetTime() const { return m_time; }
		float GetDeltaTime() { return m_deltaTime * m_timeScale; }
		float GetUnscaledDeltaTime() const { return m_deltaTime; }

		float GetTimeScale() { return m_timeScale; }
		void SetTimeScale(float timeScale) { m_timeScale = timeScale; }
	private:
		clock::time_point m_startTime;
		clock::time_point m_frameTime;
		float m_time = 0;
		float m_deltaTime = 0;
		float m_timeScale = 1;
	};

	extern Time g_time;
}