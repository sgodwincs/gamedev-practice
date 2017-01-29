#pragma once

#include <ecs/component/Collidable.hpp>
#include <ecs/component/GridPosition.hpp>
#include <ecs/component/Renderable.hpp>

namespace Game::ECS::System
{
	class SpatialPartition : public anax::System<anax::Requires<Component::Collidable, Component::GridPosition>>
	{
	private:
		std::array<std::array<std::vector<anax::Entity::Id>, 20>, 30> grid;

	public:
		struct SPData
		{
			anax::Entity::Id entityID;
			sf::Vector2i position;
		};

		void ClearGrid()
		{
			for (auto& row : grid)
			{
				for (auto& vec : row)
				{
					vec.clear();
				}
			}
		}

		const std::vector<anax::Entity::Id>& GetCell(unsigned int x, unsigned int y) const
		{
			return grid[x][y];
		}

		void Process()
		{
			ClearGrid();

			std::vector<sf::Vertex> vertices{};
			auto& entities = getEntities();

			for (auto& entity : entities)
			{
				const auto& position{ entity.getComponent<Component::GridPosition>().position };
				grid[position.x][position.y].emplace_back(entity.getId());
			}
		}
	};
}
