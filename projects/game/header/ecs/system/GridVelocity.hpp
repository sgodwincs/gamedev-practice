#pragma once

#include <ecs/component/GridPosition.hpp>
#include <ecs/component/GridVelocity.hpp>
#include <ecs/component/Movable.hpp>
#include <input/Action.hpp>

namespace Game::ECS::System
{
	class GridVelocity : public anax::System<anax::Requires<Component::GridPosition, Component::GridVelocity>>
	{
	public:
		void Process(double dt)
		{
			auto& entities = getEntities();

			for (auto& entity : entities)
			{
				auto& position{ entity.getComponent<Component::GridPosition>().position };
				auto& gridVelocity{ entity.getComponent<Component::GridVelocity>() };

				gridVelocity.timer.Update(dt);

				if (gridVelocity.timer.IsFinished())
				{
					if (gridVelocity.velocity.x > 0)
					{
						gridVelocity.direction = Component::Direction::Right;
					}
					else if (gridVelocity.velocity.x < 0)
					{
						gridVelocity.direction = Component::Direction::Left;
					}
					else if (gridVelocity.velocity.y > 0)
					{
						gridVelocity.direction = Component::Direction::Down;
					}
					else
					{
						gridVelocity.direction = Component::Direction::Up;
					}

					position += gridVelocity.velocity;

					dt = gridVelocity.timer.GetSeconds().count();
					gridVelocity.timer.Restart();
					gridVelocity.timer.Update(-dt);
				}
			}
		}
	};
}
