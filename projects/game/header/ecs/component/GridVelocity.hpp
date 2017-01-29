#pragma once

#include <utility/timer/Timer.hpp>

namespace Game::ECS::Component
{
	enum class Direction
	{
		Down,
		Left,
		Right,
		Up
	};

	struct GridVelocity : anax::Component
	{
		Direction direction;
		sf::Vector2i velocity;
		Utility::Timer timer;
	};
}
