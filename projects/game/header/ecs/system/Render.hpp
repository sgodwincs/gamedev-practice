#pragma once

#include <ecs/component/GridPosition.hpp>
#include <ecs/component/Renderable.hpp>

namespace Game::ECS::System
{
	class Render : public anax::System<anax::Requires<Component::GridPosition, Component::Renderable>>
	{
	public:
		void Process(sf::RenderTarget& renderTarget)
		{
			std::vector<sf::Vertex> vertices{};
			auto& entities = getEntities();

			for (auto& entity : entities)
			{
				auto position{ entity.getComponent<Component::GridPosition>().position };
				auto& renderable{ entity.getComponent<Component::Renderable>() };
				position *= 28;
				renderable.sprite.setPosition(static_cast<float>(position.x), static_cast<float>(position.y));
				renderTarget.draw(renderable.sprite);
			}
		}
	};
}
