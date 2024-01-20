#include "minecraft.h"
#include "math/matrix.h"

// This is just test code - showing that my controller won't work?

int main(void)
{
    DbgWriteLine("\r\nMinecraft Original Xbox Edition");
    DbgWriteLine("Developed by: napalmtorch");

    SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");
    if (SDL_Init(SDL_INIT_GAMECONTROLLER) != 0) { DbgError("Failed to initialize SDL: %s", SDL_GetError()); return 1; }
    SDL_GameControllerEventState(SDL_ENABLE);
    DbgWriteLine("Entering main loop");

    SDL_Event event;
    while (true)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_CONTROLLERDEVICEADDED)
            {
                SDL_GameController* dev = SDL_GameControllerOpen(event.cdevice.which);
                DbgWriteLine("CONTROLLER CONNECTED");
            }
            else if (event.type == SDL_CONTROLLERDEVICEREMOVED) { SDL_GameControllerClose(SDL_GameControllerFromInstanceID(event.cdevice.which)); }
            else if (event.type == SDL_CONTROLLERAXISMOTION) { DbgWriteLine("AXIS"); }
            else if (event.type == SDL_CONTROLLERBUTTONDOWN) { DbgWriteLine("BUTTON DOWN"); }
            else if (event.type == SDL_CONTROLLERBUTTONUP) { DbgWriteLine("BUTTON UP"); }
        }
        SDL_GameControllerUpdate();
    }
    return 0;
}