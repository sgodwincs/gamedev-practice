#pragma once

#include <ecs/component/Collidable.hpp>
#include <ecs/component/GridPosition.hpp>
#include <ecs/component/Renderable.hpp>
#include <ecs/component/Wall.hpp>

namespace Game::ECS::Entity
{
	inline auto CreateBlock(anax::World& world, sf::Texture& texture, unsigned int x, unsigned int y)
	{
		auto block{ world.createEntity() };

		auto& collidable{ block.addComponent<Component::Collidable>() };

		auto& gridPosition{ block.addComponent<Component::GridPosition>() };
		gridPosition.position = { static_cast<int>(x), static_cast<int>(y) };

		auto& renderable{ block.addComponent<Component::Renderable>() };
		renderable.sprite.setTexture(texture);

		auto& wall{ block.addComponent<Component::Wall>() };

		block.activate();

		return block;
	}
}
