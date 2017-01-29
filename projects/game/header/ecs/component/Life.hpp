#pragma once

#include <utility/timer/Timer.hpp>

namespace Game::ECS::Component
{
	struct Life : anax::Component
	{
		Utility::Timer timer;
	};
}
