#pragma once

#include <input/InputBuffer.hpp>
#include <state/GameStateMachine.hpp>

namespace Game
{
	class Game
	{
	private:
		Input::InputBuffer inputBuffer;
		sf::RenderWindow window;
		State::GameStateMachine stateMachine;

	public:
		static constexpr unsigned int frameRateLimit{ 120 };
		static constexpr std::chrono::milliseconds maxFrameTime{ 250 };
		static constexpr std::chrono::microseconds timeStep{ 16666 };
		static constexpr unsigned int windowHeight{ 560 };
		static constexpr const char* windowTitle{ "Game" };
		static constexpr unsigned int windowWidth{ 840 };

		Game();
		Game(const Game& other) = delete;
		Game& operator=(const Game& other) = delete;

		void GameLoop();
		void InputLoop();
		void Run();
	};
}
