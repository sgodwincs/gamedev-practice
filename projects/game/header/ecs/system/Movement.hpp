#pragma once

#include <ecs/component/GridVelocity.hpp>
#include <ecs/component/Movable.hpp>

namespace Game::ECS::System
{
	class Movement : public anax::System<anax::Requires<Component::GridVelocity, Component::Movable>>
	{
	public:
		void Process()
		{
			auto& entities = getEntities();

			for (auto& entity : entities)
			{
				auto& gridVelocity{ entity.getComponent<Component::GridVelocity>() };
				const auto& actionMap{ *entity.getComponent<Component::Movable>().map };

				if (actionMap.IsButtonPressed(Input::Action::MoveUp) &&
					gridVelocity.direction != Component::Direction::Down)
				{
					gridVelocity.velocity.x = 0;
					gridVelocity.velocity.y = -1;
				}
				else if (actionMap.IsButtonPressed(Input::Action::MoveRight) &&
					gridVelocity.direction != Component::Direction::Left)
				{
					gridVelocity.velocity.x = 1;
					gridVelocity.velocity.y = 0;
				}
				else if (actionMap.IsButtonPressed(Input::Action::MoveDown) &&
					gridVelocity.direction != Component::Direction::Up)
				{
					gridVelocity.velocity.x = 0;
					gridVelocity.velocity.y = 1;
				}
				else if (actionMap.IsButtonPressed(Input::Action::MoveLeft) &&
					gridVelocity.direction != Component::Direction::Right)
				{
					gridVelocity.velocity.x = -1;
					gridVelocity.velocity.y = 0;
				}
			}
		}
	};
}
