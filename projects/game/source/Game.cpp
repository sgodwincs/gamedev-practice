#include <Game.hpp>
#include <state/states/PlayState.hpp>

namespace Game
{
	Game::Game() :
		inputBuffer{},
		window{},
		stateMachine{ window }
	{
		stateMachine.PushState(std::make_unique<State::PlayState>());
		window.create({ windowWidth, windowHeight }, windowTitle, sf::Style::None);
		window.setActive(false);
		window.setFramerateLimit(frameRateLimit);
	}

	void Game::GameLoop()
	{
		window.setActive(true);

		auto currentTime{ std::chrono::high_resolution_clock::now() };
		auto start{ currentTime };
		std::chrono::nanoseconds accumulator{ 0 };

		while (window.isOpen())
		{
			const auto newTime{ std::chrono::high_resolution_clock::now() };
			auto frameTime{ newTime - currentTime };

			if (frameTime > maxFrameTime)
			{
				frameTime = maxFrameTime;
			}

			currentTime = newTime;
			accumulator += frameTime;

			while (accumulator >= timeStep)
			{
				stateMachine.ProcessInput(inputBuffer.RetrieveEvents(currentTime));
				stateMachine.Update(std::chrono::duration<double>(timeStep).count());
				accumulator -= timeStep;
			}

			stateMachine.Render(static_cast<double>(accumulator.count()) / std::chrono::duration_cast<std::chrono::nanoseconds>(timeStep).count());
		}
	}

	void Game::InputLoop()
	{
		sf::Event event{};

		while (window.isOpen())
		{
			if (window.waitEvent(event))
			{
				inputBuffer.BufferEvent(std::move(event));
			}
		}
	}

	void Game::Run()
	{
		std::thread gameThread{ &Game::GameLoop, this };
		InputLoop();
	}
}
