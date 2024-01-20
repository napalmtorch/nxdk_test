#include "platform/input.h"
#include "minecraft.h"

static Gamepad _gamepads[GAMEPAD_COUNT];

void InputInit()
{
    memset(_gamepads, 0, sizeof(_gamepads));

    DbgWriteLine("Initialized input manager - %u gamepads connected", InputDeviceCount());
}

void InputOnDeviceConnected(GAMEPAD_ID   id, SDL_GameController* dev)
{
    DbgWriteLine("Gamepad %u connected", id);
}

void InputOnDeviceDisconnected(GAMEPAD_ID id, SDL_GameController* dev)
{
    DbgWriteLine("Gamepad %u disconnected", id);
}

void InputOnDeviceAxisMoved(GAMEPAD_ID id, SDL_GameController* dev)
{
    DbgWriteLine("Gamepad %u axis moved", id);
}

void InputOnDeviceButtonDown(GAMEPAD_ID id, SDL_GameController* dev)
{
    DbgWriteLine("Gamepad %u button down", id);
}

void InputOnDeviceButtonUp(GAMEPAD_ID id, SDL_GameController* dev)
{
    DbgWriteLine("Gamepad %u button up", id);
}

size_t InputDeviceCount()
{
    size_t c = 0;
    for (size_t i = 0; i < GAMEPAD_COUNT; i++)
    {
        if (_gamepads[i].connected && _gamepads[i].dev != NULL) { c++; }
    }
    return c;
}