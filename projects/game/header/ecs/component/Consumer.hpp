#pragma once

namespace Game::ECS::Component
{
	struct Consumer : anax::Component
	{
		bool dead;
		std::list<anax::Entity::Id> body;
	};
}
