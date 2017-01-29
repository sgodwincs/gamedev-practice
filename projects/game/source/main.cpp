#include <Game.hpp>

int main()
{
	try
	{
		Game::Game game{};
		game.Run();
	}
	catch (const std::exception& exception)
	{
		std::cerr << "Error: " << exception.what() << std::endl;
	}
}
