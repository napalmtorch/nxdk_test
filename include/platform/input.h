#pragma once
#include "platform/common.h"
#include "math/vector2.h"
#include <SDL.h>

#define GAMEPAD_COUNT 4

typedef enum
{
    GAMEPAD1,
    GAMEPAD2,
    GAMEPAD3,
    GAMEPAD4,
} GAMEPAD_ID;

typedef enum
{
    GAMEPAD_BUTTON_A,
    GAMEPAD_BUTTON_B,
    GAMEPAD_BUTTON_X,
    GAMEPAD_BUTTON_Y,
    GAMEPAD_BUTTON_START,
    GAMEPAD_BUTTON_SELECT,
    GAMEPAD_BUTTON_BLACK,
    GAMEPAD_BUTTON_WHITE,
    GAMEPAD_BUTTON_DPAD_UP,
    GAMEPAD_BUTTON_DPAD_DOWN,
    GAMEPAD_BUTTON_DPAD_LEFT,
    GAMEPAD_BUTTON_DPAD_RIGHT,
    GAMEPAD_BUTTON_COUNT,
} GAMEPAD_BUTTON;

typedef struct
{
    SDL_GameController* dev;
    Vector2             thumb_l;
    Vector2             thumb_r;
    float               trigger_l;
    float               trigger_r;
    bool                buttons[GAMEPAD_BUTTON_COUNT];
    bool                connected;
} Gamepad;

void InputInit();
void InputOnDeviceConnected(GAMEPAD_ID id, SDL_GameController* dev);
void InputOnDeviceDisconnected(GAMEPAD_ID id, SDL_GameController* dev);
void InputOnDeviceAxisMoved(GAMEPAD_ID id, SDL_GameController* dev);
void InputOnDeviceButtonDown(GAMEPAD_ID id, SDL_GameController* dev);
void InputOnDeviceButtonUp(GAMEPAD_ID id, SDL_GameController* dev);
size_t InputDeviceCount();