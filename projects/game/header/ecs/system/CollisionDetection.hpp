#pragma once

#include <ecs/component/Collidable.hpp>
#include <ecs/component/GridPosition.hpp>
#include <ecs/component/Renderable.hpp>
#include <ecs/system/SpatialPartition.hpp>

namespace Game::ECS::System
{
	class CollisionDetection : public anax::System<anax::Requires<Component::Collidable>>
	{
	public:
		void Process(anax::World& world, const SpatialPartition& spatialPartitionSystem)
		{
			std::vector<sf::Vertex> vertices{};
			auto& entities{ getEntities() };

			for (auto& entity : entities)
			{
				entity.getComponent<Component::Collidable>().contacts.clear();
			}

			for (std::size_t i{ 0 }; i < 30; ++i)
			{
				for (std::size_t j{ 0 }; j < 20; ++j)
				{
					auto& vec = spatialPartitionSystem.GetCell(static_cast<unsigned int>(i), static_cast<unsigned int>(j));

					if (vec.size() <= 1)
					{
						continue;
					}

					for (auto it1 = vec.cbegin(); it1 != vec.cend() - 1; ++it1)
					{
						for (auto it2 = it1 + 1; it2 != vec.cend(); ++it2)
						{
							auto& contacts1{ world.getEntity(it1->index).getComponent<Component::Collidable>().contacts };
							auto& contacts2{ world.getEntity(it2->index).getComponent<Component::Collidable>().contacts };

							contacts1.emplace_back(*it2);
							contacts2.emplace_back(*it1);
						}
					}
				}
			}
		}
	};
}
