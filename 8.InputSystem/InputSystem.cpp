#include "InputSystem.h"
#include <SDL/SDL.h>
#include <cstring>


bool KeyboardState::GetKeyValue(SDL_Scancode keyCode) const
{
    return false;
}

ButtonState KeyboardState::GetKeyState(SDL_Scancode keyCode) const
{
    if (mPrevState[keyCode] == 0)
    {
        if (mCurrState[keyCode] == 0)
            return ENone;
        else
            return EPressed;
    }
    else
    {
        if (mCurrState[keyCode] == 0)
            return EReleased;
        else
            return EHeld;
    }
}





bool InputSystem::Initialize()
{
    mState.Keyboard.mCurrState = SDL_GetKeyboardState(NULL);
    memset(mState.Keyboard.mPrevState, 0, SDL_NUM_SCANCODES);

    return false;
}

void InputSystem::Shutdown()
{
}

void InputSystem::PrepareForUpdate()
{
    //МќХЬ
    memcpy(mState.Keyboard.mPrevState,
        mState.Keyboard.mCurrState,
        SDL_NUM_SCANCODES);
    //ЪѓБъ
    mState.Mouse.mPrevButtons = mState.Mouse.mCurrButtons;
    mState.Mouse.mIsRelative = false;
    mState.Mouse.mScrollWheel = Vector2::Zero;
}

void InputSystem::Update()
{
    int x = 0, y = 0;
    if (mState.Mouse.mIsRelative)
    {
        mState.Mouse.mCurrButtons =
            SDL_GetRelativeMouseState(&x, &y);
    }
    else
    {
        mState.Mouse.mCurrButtons =
            SDL_GetMouseState(&x, &y);
    }

    mState.Mouse.mMousePos.x = static_cast<float>(x);
    mState.Mouse.mMousePos.y = static_cast<float>(y);
}

void InputSystem::ProcessEvent(SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_MOUSEWHEEL:
        mState.Mouse.mScrollWheel = Vector2(
            static_cast<float>(event.wheel.x),
            static_cast<float>(event.wheel.y));
        break;
    default:
        break;
    }
}

void InputSystem::SetRelativeMouseMode(bool value)
{
    SDL_bool set = value ? SDL_TRUE : SDL_FALSE;
    SDL_SetRelativeMouseMode(set);

    mState.Mouse.mIsRelative = value;
}

bool MouseState::GetButtonValue(int button) const
{
    return false;
}

ButtonState MouseState::GetButtonState(int button) const
{
    return ButtonState();
}
