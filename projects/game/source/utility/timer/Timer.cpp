#include <utility/timer/Timer.hpp>

namespace Game::Utility
{
	Timer::Timer(const bool virtualTimer) :
		active{ false },
		virtualTimer{ virtualTimer },
		startTime{ 0 },
		time{ 0 }
	{

	}

	void Timer::AddTime(const double seconds)
	{
		time += std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>{ seconds });
	}

	void Timer::Deactivate() noexcept
	{
		active = false;
	}

	std::chrono::duration<double> Timer::GetSeconds() const noexcept
	{
		return std::chrono::duration<double>(time);
	}

	std::chrono::duration<double> Timer::GetStartTime() const noexcept
	{
		return startTime;
	}

	bool Timer::IsActive() const noexcept
	{
		return active;
	}

	bool Timer::IsFinished() const noexcept
	{
		return time <= std::chrono::nanoseconds{ 0 };
	}

	void Timer::Restart()
	{
		time = std::chrono::duration_cast<std::chrono::nanoseconds>(startTime);
	}

	void Timer::Start(const double seconds)
	{
		active = true;
		startTime = std::chrono::duration<double>{ seconds };
		time = std::chrono::duration_cast<std::chrono::nanoseconds>(startTime);
	}

	void Timer::Update(const double timeStep, const bool updateVirtual)
	{
		if (IsActive() && !IsFinished() && (!virtualTimer || updateVirtual))
		{
			time -= std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>{ timeStep });
		}
	}
}
