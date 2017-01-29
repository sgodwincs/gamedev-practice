#include <input/InputBuffer.hpp>

namespace Game::Input
{
	constexpr std::size_t InputBuffer::initialBufferReserve;

	InputBuffer::InputBuffer() :
		buffer{ initialBufferReserve } { }

	void InputBuffer::BufferEvent(const sf::Event&& event)
	{
		buffer.enqueue({ std::chrono::high_resolution_clock::now(), event });
	}

	std::vector<sf::Event> InputBuffer::RetrieveEvents(const std::chrono::high_resolution_clock::time_point& timestamp)
	{
		std::vector<sf::Event> events{};
		InputElement element{};

		while (buffer.size_approx() > 0 && buffer.peek()->first <= timestamp)
		{
			buffer.try_dequeue(element);
			events.push_back(element.second);
		}

		return events;
	}
}
