#pragma once

#include <input/ActionMap.hpp>

namespace Game::ECS::Component
{
	struct Movable : anax::Component
	{
		Input::ActionMap* map;
	};
}
