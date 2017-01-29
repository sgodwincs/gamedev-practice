#pragma once

namespace Game::Utility
{
	class Timer
	{
	private:
		bool active;
		bool virtualTimer;
		std::chrono::nanoseconds time;
		std::chrono::duration<double> startTime;

	public:
		Timer(const bool virtualTimer = true);

		void AddTime(const double seconds);
		void Deactivate() noexcept;
		std::chrono::duration<double> GetSeconds() const noexcept;
		std::chrono::duration<double> GetStartTime() const noexcept;
		bool IsActive() const noexcept;
		bool IsFinished() const noexcept;
		void Restart();
		void Start(const double seconds);
		void Update(const double timeStep, const bool updateVirtual = true);
	};
}
