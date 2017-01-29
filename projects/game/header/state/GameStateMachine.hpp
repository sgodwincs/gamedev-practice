#pragma once

#include <state/GameState.hpp>

namespace Game::State
{
	class GameStateMachine
	{
	private:
		std::vector<std::unique_ptr<GameState>> states;
		sf::RenderWindow& window;

	public:
		static constexpr std::vector<std::unique_ptr<GameState>>::size_type initialStateReserve{ 5 };

		GameStateMachine(sf::RenderWindow& window);
		GameStateMachine(const GameStateMachine& other) = delete;
		GameStateMachine& operator=(const GameStateMachine& other) = delete;

		void ChangeState(std::unique_ptr<GameState> state);
		sf::RenderWindow& GetWindow();
		void PopState();
		void ProcessInput(const std::vector<sf::Event>& events);
		void PushState(std::unique_ptr<GameState> state);
		void Render(double alpha);
		void Update(double timeStep);
	};
}
