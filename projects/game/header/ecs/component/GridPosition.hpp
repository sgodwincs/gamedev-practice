#pragma once

namespace Game::ECS::Component
{
	struct GridPosition : anax::Component
	{
		sf::Vector2i position;
	};
}
