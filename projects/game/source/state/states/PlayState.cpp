#include <state/states/EndState.hpp>
#include <state/states/PlayState.hpp>
#include <ecs/components.hpp>
#include <ecs/entities.hpp>
#include <ecs/systems.hpp>

namespace Game::State
{
	PlayState::PlayState() :
		renderSystem{}
	{
		actionMap.MapAction(Input::Action::MoveUp, Input::Key::Up);
		actionMap.MapAction(Input::Action::MoveRight, Input::Key::Right);
		actionMap.MapAction(Input::Action::MoveDown, Input::Key::Down);
		actionMap.MapAction(Input::Action::MoveLeft, Input::Key::Left);
		
		foodTexture.loadFromFile("asset/texture/food.png");
		snakeBodyTexture.loadFromFile("asset/texture/snake_body.png");
		snakeHeadTexture.loadFromFile("asset/texture/snake_head.png");
		wallTexture.loadFromFile("asset/texture/wall.png");

		for (std::size_t y{ 0 }; y < 20; ++y)
		{
			ECS::Entity::CreateBlock(world, wallTexture, 0, static_cast<unsigned int>(y));
			ECS::Entity::CreateBlock(world, wallTexture, 29, static_cast<unsigned int>(y));
		}

		for (std::size_t x{ 1 }; x < 29; ++x)
		{
			ECS::Entity::CreateBlock(world, wallTexture, static_cast<unsigned int>(x), 0);
			ECS::Entity::CreateBlock(world, wallTexture, static_cast<unsigned int>(x), 19);
		}

		snakeEntityID = ECS::Entity::CreateSnakeHead(world, actionMap, snakeHeadTexture, snakeBodyTexture).getId();
		ECS::Entity::CreateFood(world, foodTexture);

		world.addSystem(collisionDetectionSystem);
		world.addSystem(consumerSystem);
		world.addSystem(consumerCollisionSystem);
		world.addSystem(edibleCollisionSystem);
		world.addSystem(gridVelocitySystem);
		world.addSystem(lifeSystem);
		world.addSystem(movementSystem);
		world.addSystem(renderSystem);
		world.addSystem(spatialPartitionSystem);
	}

	PlayState::~PlayState()
	{


	}

	void PlayState::Entering(GameStateMachine& stateMachine)
	{
		std::cout << "Entering\n";
	}

	void PlayState::Exiting(GameStateMachine& stateMachine)
	{
		std::cout << "Exiting\n";
	}

	void PlayState::Obscuring(GameStateMachine& stateMachine)
	{
		std::cout << "Obscuring\n";
	}

	void PlayState::ProcessInput(GameStateMachine& stateMachine, const std::vector<sf::Event>& events)
	{
		actionMap.ProcessInput(events);
	}

	void PlayState::Render(GameStateMachine& stateMachine, double alpha)
	{
		auto& window = stateMachine.GetWindow();
		window.clear(sf::Color::White);
		renderSystem.Process(stateMachine.GetWindow());
		window.display();
	}

	void PlayState::Revealing(GameStateMachine& stateMachine)
	{
		std::cout << "Revealing\n";
	}

	void PlayState::Update(GameStateMachine& stateMachine, double timeStep)
	{
		movementSystem.Process();
		gridVelocitySystem.Process(timeStep);
		spatialPartitionSystem.Process();
		collisionDetectionSystem.Process(world, spatialPartitionSystem);
		consumerCollisionSystem.Process();
		edibleCollisionSystem.Process(foodTexture);
		consumerSystem.Process(snakeBodyTexture, timeStep);
		lifeSystem.Process(timeStep);

		world.refresh();

		if (world.getEntity(snakeEntityID.index).getComponent<ECS::Component::Consumer>().dead)
		{
			stateMachine.ChangeState(std::make_unique<EndState>());
		}
	}
}
