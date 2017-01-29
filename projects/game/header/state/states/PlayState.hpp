#pragma once

#include <ecs/systems.hpp>
#include <state/GameState.hpp>
#include <state/GameStateMachine.hpp>

namespace Game::State
{
	class PlayState : public GameState
	{
	private:
		anax::Entity::Id snakeEntityID;

		sf::Texture foodTexture;
		sf::Texture snakeBodyTexture;
		sf::Texture snakeHeadTexture;
		sf::Texture wallTexture;

		ECS::System::CollisionDetection collisionDetectionSystem;
		ECS::System::Consumer consumerSystem;
		ECS::System::ConsumerCollision consumerCollisionSystem;
		ECS::System::EdibleCollision edibleCollisionSystem;
		ECS::System::GridVelocity gridVelocitySystem;
		ECS::System::Life lifeSystem;
		ECS::System::Movement movementSystem;
		ECS::System::Render renderSystem;
		ECS::System::SpatialPartition spatialPartitionSystem;

	public:
		PlayState();
		~PlayState();
		PlayState(const PlayState& other) = delete;
		PlayState& operator=(const PlayState& other) = delete;

		void Entering(GameStateMachine& stateMachine) override;
		void Exiting(GameStateMachine& stateMachine) override;
		void Obscuring(GameStateMachine& stateMachine) override;
		void ProcessInput(GameStateMachine& stateMachine, const std::vector<sf::Event>& events) override;
		void Render(GameStateMachine& stateMachine, double alpha) override;
		void Revealing(GameStateMachine& stateMachine) override;
		void Update(GameStateMachine& stateMachine, double timeStep) override;
	};
}
