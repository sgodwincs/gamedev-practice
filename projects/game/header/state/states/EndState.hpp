#pragma once

#include <state/GameState.hpp>
#include <state/GameStateMachine.hpp>

namespace Game::State
{
	class EndState : public GameState
	{
	private:
		sf::Font font;

	public:
		EndState();
		~EndState();
		EndState(const EndState& other) = delete;
		EndState& operator=(const EndState& other) = delete;

		void Entering(GameStateMachine& stateMachine) override;
		void Exiting(GameStateMachine& stateMachine) override;
		void Obscuring(GameStateMachine& stateMachine) override;
		void ProcessInput(GameStateMachine& stateMachine, const std::vector<sf::Event>& events) override;
		void Render(GameStateMachine& stateMachine, double alpha) override;
		void Revealing(GameStateMachine& stateMachine) override;
		void Update(GameStateMachine& stateMachine, double timeStep) override;
	};
}
