#pragma once

#include <ecs/component/Collidable.hpp>
#include <ecs/component/Consumer.hpp>
#include <ecs/component/GridPosition.hpp>
#include <ecs/component/GridVelocity.hpp>
#include <ecs/component/Life.hpp>
#include <ecs/component/Movable.hpp>
#include <ecs/component/Renderable.hpp>
#include <ecs/component/Wall.hpp>
#include <input/ActionMap.hpp>

namespace Game::ECS::Entity
{
	inline auto CreateSnakeBody(anax::World& world, sf::Texture& texture, unsigned int x, unsigned int y, double lifeTime)
	{
		auto snakeBody{ world.createEntity() };

		auto& collidable{ snakeBody.addComponent<Component::Collidable>() };

		auto& gridPosition{ snakeBody.addComponent<Component::GridPosition>() };
		gridPosition.position = { static_cast<int>(x), static_cast<int>(y) };

		auto& life{ snakeBody.addComponent<Component::Life>() };
		life.timer.Start(lifeTime);

		auto& renderable{ snakeBody.addComponent<Component::Renderable>() };
		renderable.sprite.setTexture(texture);

		auto& wall{ snakeBody.addComponent<Component::Wall>() };

		snakeBody.activate();
		return snakeBody;
	}

	inline auto CreateSnakeHead(anax::World& world, Input::ActionMap& map, sf::Texture& headTexture, sf::Texture& bodyTexture)
	{
		auto snakeHead{ world.createEntity() };

		auto& collidable{ snakeHead.addComponent<Component::Collidable>() };

		auto& consumer{ snakeHead.addComponent<Component::Consumer>() };
		consumer.dead = false;

		auto& gridPosition{ snakeHead.addComponent<Component::GridPosition>() };
		gridPosition.position = { 15, 10 };

		auto& gridVelocity{ snakeHead.addComponent<Component::GridVelocity>() };
		gridVelocity.direction = Component::Direction::Right;
		gridVelocity.velocity = { 1, 0 };
		gridVelocity.timer.Start(.15);

		auto& movable{ snakeHead.addComponent<Component::Movable>() };
		movable.map = &map;

		auto& renderable{ snakeHead.addComponent<Component::Renderable>() };
		renderable.sprite.setTexture(headTexture);

		consumer.body.emplace_front(CreateSnakeBody(world, bodyTexture, 14, 10, 0.3).getId());
		consumer.body.emplace_front(CreateSnakeBody(world, bodyTexture, 13, 10, 0.15).getId());

		snakeHead.activate();
		return snakeHead;
	}
}
