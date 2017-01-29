#include <input/ActionMap.hpp>
#include <utility/assert/ppk_assert.hpp>

namespace Game::Input
{
    ActionMap::ActionMap() :
        keyboardBuffer{},
        map{}
    {

    }

    void ActionMap::ClearMap() noexcept
    {
        map.clear();
    }

    bool ActionMap::DidRangeChange(const ActionID actionID) const
    {
        PPK_ASSERT(IsMapped(actionID), "ActionMap::DidRangeChange - Unmapped action ID - Cannot check state");

        return GetRangeStateDelta(actionID) != 0.0;
    }

    ButtonState ActionMap::GetCurrentButtonState(const ActionID actionID) const
    {
        PPK_ASSERT(IsMapped(actionID), "ActionMap::GetCurrentButtonState - Unmapped action ID - Cannot check state");

        auto& mappedAction = map.at(actionID);
        return mappedAction.deviceBuffer->GetCurrentButtonState(mappedAction.deviceInputID);
    }

    RangeState ActionMap::GetCurrentRangeState(const ActionID actionID) const
    {
        PPK_ASSERT(IsMapped(actionID), "ActionMap::GetCurrentRangeState - Unmapped action ID - Cannot check state");

        auto& mappedAction = map.at(actionID);
        return mappedAction.deviceBuffer->GetCurrentRangeState(mappedAction.deviceInputID);
    }

    ButtonState ActionMap::GetPreviousButtonState(const ActionID actionID) const
    {
        PPK_ASSERT(IsMapped(actionID), "ActionMap::GetPreviousButtonState - Unmapped action ID - Cannot check state");

        auto& mappedAction = map.at(actionID);
        return mappedAction.deviceBuffer->GetPreviousButtonState(mappedAction.deviceInputID);
    }

    RangeState ActionMap::GetPreviousRangeState(const ActionID actionID) const
    {
        PPK_ASSERT(IsMapped(actionID), "ActionMap::GetPreviousRangeState - Unmapped action ID - Cannot check state");

        auto& mappedAction = map.at(actionID);
        return mappedAction.deviceBuffer->GetPreviousRangeState(mappedAction.deviceInputID);
    }

    RangeStateDelta ActionMap::GetRangeStateDelta(const ActionID actionID) const
    {
        PPK_ASSERT(IsMapped(actionID), "ActionMap::GetRangeStateDelta - Unmapped action ID - Cannot check state");

        return GetCurrentRangeState(actionID) - GetPreviousRangeState(actionID);
    }

    bool ActionMap::IsButtonDown(const ActionID actionID) const
    {
        PPK_ASSERT(IsMapped(actionID), "ActionMap::IsButtonDown - Unmapped action ID - Cannot check state");

        return GetCurrentButtonState(actionID) == ButtonState::Down;
    }

    bool ActionMap::IsButtonPressed(const ActionID actionID) const
    {
        PPK_ASSERT(IsMapped(actionID), "ActionMap::IsButtonPressed - Unmapped action ID - Cannot check state");

        return GetCurrentButtonState(actionID) == ButtonState::Pressed;
    }

    bool ActionMap::IsButtonReleased(const ActionID actionID) const
    {
        PPK_ASSERT(IsMapped(actionID), "ActionMap::IsButtonReleased - Unmapped action ID - Cannot check state");

        return GetCurrentButtonState(actionID) == ButtonState::Released;
    }

    bool ActionMap::IsButtonUp(const ActionID actionID) const
    {
        PPK_ASSERT(IsMapped(actionID), "ActionMap::IsButtonDown - Unmapped action ID - Cannot check state");

        return GetCurrentButtonState(actionID) == ButtonState::Up;
    }

    bool ActionMap::IsMapped(const ActionID actionID) const
    {
        return map.find(actionID) != map.cend();
    }

    void ActionMap::MapAction(const ActionID actionID, const Key key)
    {
        map[actionID] = {
            &keyboardBuffer,
            static_cast<DeviceInputID>(key)
        };
    }

    void ActionMap::ProcessInput(const std::vector<sf::Event>& events)
    {
        keyboardBuffer.SwapBuffers();

        for (auto& event : events)
        {
            switch (event.type)
            {
                case sf::Event::KeyPressed:
                case sf::Event::KeyReleased:
                    keyboardBuffer.ProcessInput(event);
                    break;
            }
        }
    }

    bool ActionMap::UnmapAction(const ActionID actionID)
    {
        return map.erase(actionID) == 1;
    }

    bool ActionMap::WasButtonDown(const ActionID actionID) const
    {
        PPK_ASSERT(IsMapped(actionID), "ActionMap::WasButtonDown - Unmapped action ID - Cannot check state");

        return GetPreviousButtonState(actionID) == ButtonState::Down;
    }

    bool ActionMap::WasButtonPressed(const ActionID actionID) const
    {
        PPK_ASSERT(IsMapped(actionID), "ActionMap::WasButtonPressed - Unmapped action ID - Cannot check state");

        return GetPreviousButtonState(actionID) == ButtonState::Pressed;
    }

    bool ActionMap::WasButtonReleased(const ActionID actionID) const
    {
        PPK_ASSERT(IsMapped(actionID), "ActionMap::WasButtonReleased - Unmapped action ID - Cannot check state");

        return GetPreviousButtonState(actionID) == ButtonState::Released;
    }

    bool ActionMap::WasButtonUp(const ActionID actionID) const
    {
        PPK_ASSERT(IsMapped(actionID), "ActionMap::WasButtonUp - Unmapped action ID - Cannot check state");

        return GetPreviousButtonState(actionID) == ButtonState::Up;
    }
}
