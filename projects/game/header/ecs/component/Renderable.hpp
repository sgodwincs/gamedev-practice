#pragma once

namespace Game::ECS::Component
{
	struct Renderable : anax::Component
	{
		sf::Sprite sprite;
	};
}
