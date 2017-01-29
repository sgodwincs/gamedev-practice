#pragma once

#include <input/ActionMap.hpp>

namespace Game::State
{
	class GameStateMachine;

	class GameState
	{
	protected:
		Input::ActionMap actionMap;
		anax::World world;

	public:
		GameState() :
			actionMap{},
			world{}  { }
		virtual ~GameState() { };
		GameState(const GameState& other) = delete;
		GameState& operator=(const GameState& other) = delete;

		virtual void Entering(GameStateMachine& stateMachine) = 0;
		virtual void Exiting(GameStateMachine& stateMachine) = 0;
		virtual void Obscuring(GameStateMachine& stateMachine) = 0;
		virtual void ProcessInput(GameStateMachine& stateMachine, const std::vector<sf::Event>& events) = 0;
		virtual void Render(GameStateMachine& stateMachine, double alpha) = 0;
		virtual void Revealing(GameStateMachine& stateMachine) = 0;
		virtual void Update(GameStateMachine& stateMachine, double timeStep) = 0;
	};
}
