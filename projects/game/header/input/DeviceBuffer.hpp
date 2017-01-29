#pragma once

#include <input/Action.hpp>

namespace Game::Input
{
    class DeviceBuffer
    {
    public:
        virtual void ProcessInput(const sf::Event& event) = 0;
        virtual void SwapBuffers() = 0;
        virtual ButtonState GetCurrentButtonState(const DeviceInputID inputID) const = 0;
        virtual ButtonState GetPreviousButtonState(const DeviceInputID inputID) const = 0;
        virtual RangeState GetCurrentRangeState(const DeviceInputID inputID) const = 0;
        virtual RangeState GetPreviousRangeState(const DeviceInputID inputID) const = 0;
    };
}
