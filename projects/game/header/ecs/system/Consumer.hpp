#pragma once

#include <ecs/component/Consumer.hpp>
#include <ecs/component/GridPosition.hpp>
#include <ecs/component/GridVelocity.hpp>
#include <ecs/entity/Snake.hpp>

namespace Game::ECS::System
{
	class Consumer : public anax::System<anax::Requires<Component::Consumer, Component::GridPosition, Component::GridVelocity>>
	{
	public:
		void Process(sf::Texture& texture, double dt)
		{
			auto& entities = getEntities();

			for (auto& entity : entities)
			{
				const auto& position{ entity.getComponent<Component::GridPosition>().position };
				auto& timer{ entity.getComponent<Component::GridVelocity>().timer };
				auto& body{ entity.getComponent<Component::Consumer>().body };

				for (auto it = body.begin(); it != body.end();)
				{
					if (!getWorld().isActivated(getWorld().getEntity(it->index)))
					{
						it = body.erase(it);
					}
					else
					{
						++it;
					}
				}
				
				if (timer.GetSeconds().count() - dt <= 0)
				{
					body.emplace_front(ECS::Entity::CreateSnakeBody(getWorld(), texture, position.x, position.y, body.size() * 0.15).getId());
				}
			}
		}
	};
}
