#pragma once

#include <ecs/component/Life.hpp>

namespace Game::ECS::System
{
	class Life : public anax::System<anax::Requires<Component::Life>>
	{
	public:
		void Process(double dt)
		{
			auto& entities = getEntities();

			for (auto& entity : entities)
			{
				auto& timer{ entity.getComponent<Component::Life>().timer };
				timer.Update(dt);

				if (timer.IsFinished())
				{
					getWorld().killEntity(getWorld().getEntity(entity.getId().index));
				}
			}
		}
	};
}
