#pragma once

#include <utility/queue/readerwriterqueue.hpp>

namespace Game::Input
{
	class InputBuffer
	{
	private:
		using InputElement = std::pair<std::chrono::high_resolution_clock::time_point, sf::Event>;

		static constexpr std::size_t initialBufferReserve{ 100 };

		moodycamel::ReaderWriterQueue<InputElement> buffer;

	public:
		InputBuffer();
		InputBuffer(const InputBuffer& other) = delete;
		InputBuffer& operator=(const InputBuffer& other) = delete;

		void BufferEvent(const sf::Event&& event);
		std::vector<sf::Event> RetrieveEvents(const std::chrono::high_resolution_clock::time_point& timestamp);
	};
}

