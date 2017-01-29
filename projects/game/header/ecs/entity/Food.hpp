#pragma once

#include <ecs/component/Collidable.hpp>
#include <ecs/component/Edible.hpp>
#include <ecs/component/GridPosition.hpp>
#include <ecs/component/GridVelocity.hpp>
#include <ecs/component/Movable.hpp>
#include <ecs/component/Renderable.hpp>
#include <input/ActionMap.hpp>

namespace Game::ECS::Entity
{
	inline auto CreateFood(anax::World& world, sf::Texture& texture, unsigned int x, unsigned int y)
	{
		auto food{ world.createEntity() };

		auto& collidable{ food.addComponent<Component::Collidable>() };

		auto& edible{ food.addComponent<Component::Edible>() };

		auto& gridPosition{ food.addComponent<Component::GridPosition>() };
		gridPosition.position = { static_cast<int>(x), static_cast<int>(y) };

		auto& renderable{ food.addComponent<Component::Renderable>() };
		renderable.sprite.setTexture(texture);

		food.activate();
	}

	inline auto CreateFood(anax::World& world, sf::Texture& texture)
	{
		std::mt19937 rng(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
		std::uniform_int_distribution<unsigned int> xDist(1, 28);
		std::uniform_int_distribution<unsigned int> yDist(1, 18);

		return CreateFood(world, texture, xDist(rng), yDist(rng));
	}
}
