#include <state/GameStateMachine.hpp>
#include <utility/assert/ppk_assert.hpp>

namespace Game::State
{
	constexpr std::vector<std::unique_ptr<GameState>>::size_type GameStateMachine::initialStateReserve;

	GameStateMachine::GameStateMachine(sf::RenderWindow& window) :
		states{},
		window{ window }
	{
		states.reserve(initialStateReserve);
	}

	void GameStateMachine::ChangeState(std::unique_ptr<GameState> state)
	{
		PPK_ASSERT_FATAL(!states.empty(), "GameStateMachine::ChangeState - Stack is empty: Cannot change state");

		states.back()->Exiting(*this);
		states.pop_back();

		states.push_back(std::move(state));
		states.back()->Entering(*this);
	}

	sf::RenderWindow& GameStateMachine::GetWindow()
	{
		return window;
	}

	void GameStateMachine::PopState()
	{
		PPK_ASSERT_FATAL(!states.empty(), "GameStateMachine::PopState - Stack is empty: Cannot pop state");

		states.back()->Exiting(*this);
		states.pop_back();

		if (!states.empty())
		{
			states.back()->Revealing(*this);
		}
	}

	void GameStateMachine::ProcessInput(const std::vector<sf::Event>& events)
	{
		PPK_ASSERT_FATAL(!states.empty(),
			"GameStateMachine::ProcessInput - Stack is empty: Cannot process input via state");

		states.back()->ProcessInput(*this, events);
	}

	void GameStateMachine::PushState(std::unique_ptr<GameState> state)
	{
		if (!states.empty())
		{
			states.back()->Obscuring(*this);
		}

		states.push_back(std::move(state));
		states.back()->Entering(*this);
	}

	void GameStateMachine::Render(double alpha)
	{
		PPK_ASSERT_FATAL(!states.empty(), "GameStateMachine::Render - Stack is empty: Cannot render state");

		states.back()->Render(*this, alpha);
	}

	void GameStateMachine::Update(double timeStep)
	{
		PPK_ASSERT_FATAL(!states.empty(), "GameStateMachine::Update - Stack is empty: Cannot update state");

		states.back()->Update(*this, timeStep);
	}
}
