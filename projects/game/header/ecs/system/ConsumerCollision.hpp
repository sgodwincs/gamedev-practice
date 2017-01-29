#pragma once

#include <ecs/component/Collidable.hpp>
#include <ecs/component/Consumer.hpp>
#include <ecs/component/Edible.hpp>
#include <ecs/component/Life.hpp>

namespace Game::ECS::System
{
	class ConsumerCollision : public anax::System<anax::Requires<Component::Consumer, Component::Collidable>>
	{
	public:
		void Process()
		{
			auto& world = getWorld();
			auto& entities = getEntities();

			for (auto& entity : entities)
			{
				const auto& contacts{ entity.getComponent<Component::Collidable>().contacts };

				for (auto& contactEntityID : contacts)
				{
					if (world.getEntity(contactEntityID.index).hasComponent<Component::Edible>())
					{
						auto& body{ entity.getComponent<Component::Consumer>().body };
						
						for (auto it = body.begin(); it != body.end(); ++it)
						{
							auto& entity = getWorld().getEntity(it->index);

							if (entity.isValid())
							{
								getWorld().getEntity(it->index).getComponent<Component::Life>().timer.AddTime(0.15);
							}
						}
					}
					else if (world.getEntity(contactEntityID.index).hasComponent<Component::Wall>())
					{
						entity.getComponent<Component::Consumer>().dead = true;
					}
				}
			}
		}
	};
}
