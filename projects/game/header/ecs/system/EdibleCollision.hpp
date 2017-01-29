#pragma once

#include <ecs/component/Consumer.hpp>
#include <ecs/component/Collidable.hpp>
#include <ecs/component/Edible.hpp>
#include <ecs/entity/Food.hpp>

namespace Game::ECS::System
{
	class EdibleCollision : public anax::System<anax::Requires<Component::Collidable, Component::Edible>>
	{
	public:
		void Process(sf::Texture& texture)
		{
			auto& entities = getEntities();
			auto& world = getWorld();

			for (auto& entity : entities)
			{
				const auto& contacts{ entity.getComponent<Component::Collidable>().contacts };

				for (auto& contactEntityID : contacts)
				{
					if (world.getEntity(contactEntityID.index).hasComponent<Component::Consumer>())
					{
						world.killEntity(world.getEntity(entity.getId().index));
						ECS::Entity::CreateFood(world, texture);
					}
				}
			}
		}
	};
}
