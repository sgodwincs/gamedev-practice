#pragma once

#include <input/Action.hpp>
#include <input/KeyboardBuffer.hpp>

namespace Game::Input
{
    class ActionMap
    {
    private:
        struct MappedAction
        {
            DeviceBuffer* deviceBuffer;
            DeviceInputID deviceInputID;
        };

        KeyboardBuffer keyboardBuffer;
        std::unordered_map<ActionID, MappedAction> map;

    public:
		ActionMap();
        ActionMap(const ActionMap& other) = delete;
        ActionMap& operator=(const ActionMap& other) = delete;

        void ClearMap() noexcept;
        bool DidRangeChange(const ActionID actionID) const;
        ButtonState GetCurrentButtonState(const ActionID actionID) const;
        RangeState GetCurrentRangeState(const ActionID actionID) const;
        ButtonState GetPreviousButtonState(const ActionID actionID) const;
        RangeState GetPreviousRangeState(const ActionID actionID) const;
        RangeStateDelta GetRangeStateDelta(const ActionID actionID) const;
        bool IsButtonDown(const ActionID actionID) const;
        bool IsButtonPressed(const ActionID actionID) const;
        bool IsButtonReleased(const ActionID actionID) const;
        bool IsButtonUp(const ActionID actionID) const;
        bool IsMapped(const ActionID actionID) const;
        void MapAction(const ActionID actionID, const Key button);
        void ProcessInput(const std::vector<sf::Event>& events);
        bool UnmapAction(const ActionID actionID);
        bool WasButtonDown(const ActionID actionID) const;
        bool WasButtonPressed(const ActionID actionID) const;
        bool WasButtonReleased(const ActionID actionID) const;
        bool WasButtonUp(const ActionID actionID) const;
    };
}
