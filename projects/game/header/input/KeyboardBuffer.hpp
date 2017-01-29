#pragma once

#include <input/Action.hpp>
#include <input/DeviceBuffer.hpp>

namespace Game::Input
{
    class KeyboardBuffer : public DeviceBuffer
    {
    private:
        using KeyboardBufferArray = std::array<ButtonState, static_cast<std::size_t>(Key::Count)>;

        std::unique_ptr<KeyboardBufferArray> currentBuffer;
        std::unique_ptr<KeyboardBufferArray> previousBuffer;

    public:
		KeyboardBuffer();
        KeyboardBuffer(const KeyboardBuffer& other) = delete;
        KeyboardBuffer& operator=(const KeyboardBuffer& other) = delete;

        void ProcessInput(const sf::Event& event) override;
        void SwapBuffers() override;
        ButtonState GetCurrentButtonState(const DeviceInputID inputID) const override;
        ButtonState GetPreviousButtonState(const DeviceInputID inputID) const override;
        RangeState GetCurrentRangeState(const DeviceInputID inputID) const override;
        RangeState GetPreviousRangeState(const DeviceInputID inputID) const override;
    };
}
