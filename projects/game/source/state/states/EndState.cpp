#include <state/states/EndState.hpp>

namespace Game::State
{
	EndState::EndState()
	{
		sf::err().rdbuf(std::cout.rdbuf());

		if (!font.loadFromFile("asset/font/arial.ttf"))
		{
			
		}
	}

	EndState::~EndState()
	{


	}

	void EndState::Entering(GameStateMachine& stateMachine)
	{
		std::cout << "Entering\n";
	}

	void EndState::Exiting(GameStateMachine& stateMachine)
	{
		std::cout << "Exiting\n";
	}

	void EndState::Obscuring(GameStateMachine& stateMachine)
	{
		std::cout << "Obscuring\n";
	}

	void EndState::ProcessInput(GameStateMachine& stateMachine, const std::vector<sf::Event>& events)
	{
		actionMap.ProcessInput(events);
	}

	void EndState::Render(GameStateMachine& stateMachine, double alpha)
	{
		auto& window = stateMachine.GetWindow();
		window.clear(sf::Color::White);
		
		sf::Text text;
		text.setFont(font);
		text.setString("Game over!");
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::Red);
		text.setStyle(sf::Text::Bold);
		text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
		text.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

		window.draw(text);
		window.display();
	}

	void EndState::Revealing(GameStateMachine& stateMachine)
	{
		std::cout << "Revealing\n";
	}

	void EndState::Update(GameStateMachine& stateMachine, double timeStep)
	{

	}
}
