#pragma once

namespace Game::ECS::Component
{
	struct Collidable : anax::Component
	{
		std::vector<anax::Entity::Id> contacts;
	};
}
