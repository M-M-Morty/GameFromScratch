#pragma once
#include <SDL/SDL_scancode.h>
#include <SDL/SDL_gamecontroller.h>
#include <SDL/SDL_mouse.h>
#include "Math.h"

enum ButtonState
{
	ENone,
	EPressed,
	EReleased,
	EHeld
};

class KeyboardState
{
public:
	//InputSystem可以轻松更新state
	friend class InputSystem;
	// Get just the boolean true/false value of key
	bool GetKeyValue(SDL_Scancode keyCode) const;
	// Get a state based on current and previous frame
	ButtonState GetKeyState(SDL_Scancode keyCode) const;
private:
	const Uint8* mCurrState;
	Uint8 mPrevState[SDL_NUM_SCANCODES];
};

class MouseState
{
public:
	friend class InputSystem;

	// For mouse position
	const Vector2& GetPosition() const { return mMousePos; }
	const Vector2& GetScrollWheel() const { return mScrollWheel; }
	bool IsRelative() const { return mIsRelative; }

	// For buttons
	bool GetButtonValue(int button) const;
	ButtonState GetButtonState(int button) const;
private:
	// Store current mouse position
	Vector2 mMousePos;
	// Motion of scroll wheel
	Vector2 mScrollWheel;
	// Store button data
	Uint32 mCurrButtons;
	Uint32 mPrevButtons;
	// Are we in relative mouse mode
	bool mIsRelative;
};

struct  InputState
{
	KeyboardState Keyboard;
	MouseState Mouse;
};

class InputSystem
{
private:
	InputState mState;
public:
	bool Initialize();
	void Shutdown();
	// SDL_PollEvents循环前调用
	void PrepareForUpdate();
	// SDL_PollEvents循环后调用
	void Update();
	void ProcessEvent(union SDL_Event& event);

	const InputState& GetState() const { return mState; }

	void SetRelativeMouseMode(bool value);
};