#include <input/KeyboardBuffer.hpp>
#include <utility/assert/ppk_assert.hpp>

namespace Game::Input
{
    KeyboardBuffer::KeyboardBuffer() :
        currentBuffer{std::make_unique<KeyboardBufferArray>()},
        previousBuffer{std::make_unique<KeyboardBufferArray>()}
    {
        for (KeyboardBufferArray::size_type i = 0; i < static_cast<KeyboardBufferArray::size_type>(Key::Count); ++i)
        {
            (*currentBuffer)[i] = ButtonState::Up;
            (*previousBuffer)[i] = ButtonState::Up;
        }
    }

    void KeyboardBuffer::ProcessInput(const sf::Event& event)
    {
        PPK_ASSERT_FATAL(
            event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased,
            "KeyboardBuffer::ProcessInput - Invalid event type: Cannot process input");

        if (event.key.code == sf::Keyboard::Unknown)
        {
            return;
        }

        KeyboardBufferArray::size_type key = static_cast<KeyboardBufferArray::size_type>(event.key.code);

        PPK_ASSERT_FATAL(
            key < static_cast<KeyboardBufferArray::size_type>(Key::Count),
            "KeyboardBuffer::ProcessInput - Invalid key code: Cannot process input");

        if (event.type == sf::Event::KeyPressed)
        {
            if ((*previousBuffer)[key] == ButtonState::Pressed ||
                (*previousBuffer)[key] == ButtonState::Down)
            {
                (*currentBuffer)[key] = ButtonState::Down;
            }
            else
            {
                (*currentBuffer)[key] = ButtonState::Pressed;
            }
        }
        else
        {
            (*currentBuffer)[key] = ButtonState::Released;
        }
    }

    void KeyboardBuffer::SwapBuffers()
    {
        using std::swap;
        swap(currentBuffer, previousBuffer);

        for (KeyboardBufferArray::size_type i = 0; i < static_cast<KeyboardBufferArray::size_type>(Key::Count); ++i)
        {
            auto previousButtonState = (*previousBuffer)[i];

            switch ((*previousBuffer)[i])
            {
                case ButtonState::Down:
                case ButtonState::Pressed:
                    (*currentBuffer)[i] = ButtonState::Down;
                    break;
                case ButtonState::Released:
                case ButtonState::Up:
                    (*currentBuffer)[i] = ButtonState::Up;
                    break;
            }
        }
    }

    ButtonState KeyboardBuffer::GetCurrentButtonState(const DeviceInputID inputID) const
    {
        PPK_ASSERT_FATAL(
            inputID < static_cast<KeyboardBufferArray::size_type>(Key::Count),
            "KeyboardBuffer::GetCurrentButtonState - Invalid key code: Cannot process input");

        return (*currentBuffer)[static_cast<KeyboardBufferArray::size_type>(inputID)];
    }

    ButtonState KeyboardBuffer::GetPreviousButtonState(const DeviceInputID inputID) const
    {
        PPK_ASSERT_FATAL(
            inputID < static_cast<KeyboardBufferArray::size_type>(Key::Count),
            "KeyboardBuffer::GetPreviousButtonState - Invalid key code: Cannot process input");

        return (*previousBuffer)[static_cast<KeyboardBufferArray::size_type>(inputID)];
    }

    RangeState KeyboardBuffer::GetCurrentRangeState(const DeviceInputID inputID) const
    {
        PPK_ASSERT_FATAL(
            false,
            "KeyboardBuffer::GetCurrentRangeState - "
            "KeyboardBuffer does not support range state: "
            "Method cannot be called");

        return 0;
    }

    RangeState KeyboardBuffer::GetPreviousRangeState(const DeviceInputID inputID) const
    {
        PPK_ASSERT_FATAL(
            false,
            "KeyboardBuffer::GetPreviousRangeState - "
            "KeyboardBuffer does not support range state: "
            "Method cannot be called");

        return 0;
    }
}
