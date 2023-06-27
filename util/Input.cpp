#include "Input.h"
#include <DxLib.h>

namespace 
{
	int keypadState;
	int lastKeypadState;
	char keystate[256];
	char lastKeystate[256];
	int mouseState;
	int lastMouseState;
}

namespace Input {

	void update()
	{
		for (int i = 0; i < _countof(lastKeystate); ++i) {
			lastKeystate[i] = keystate[i];
		}
		lastMouseState = mouseState;
		GetHitKeyStateAll(keystate);
		mouseState = GetMouseInput();
	}

	bool isPress(InputType type)
	{
		if (type == InputType::next) {
			return lastKeystate[KEY_INPUT_RETURN];
		}
		if (type == InputType::right) {
			return lastKeystate[KEY_INPUT_D];
		}
		if (type == InputType::left) {
			return lastKeystate[KEY_INPUT_A];
		}
		if (type == InputType::up) {
			return lastKeystate[KEY_INPUT_W];
		}
		if (type == InputType::down) {
			return lastKeystate[KEY_INPUT_S];
		}
		if (type == InputType::shot) {
			return mouseState;
		}
		return false;
	}

	bool isTrigger(InputType type)
	{
		if (type == InputType::next) {
			return !lastKeystate[KEY_INPUT_RETURN] &&
				keystate[KEY_INPUT_RETURN];
		}
		if (type == InputType::right) {
			return !lastKeystate[KEY_INPUT_D] &&
				keystate[KEY_INPUT_D];
		}
		if (type == InputType::left) {
			return !lastKeystate[KEY_INPUT_A] &&
				keystate[KEY_INPUT_A];
		}
		if (type == InputType::up) {
			return !lastKeystate[KEY_INPUT_W] &&
				keystate[KEY_INPUT_W];
		}
		if (type == InputType::down) {
			return !lastKeystate[KEY_INPUT_S] &&
				keystate[KEY_INPUT_S];
		}
		if (type == InputType::shot) {
			return !lastMouseState &&
				mouseState;
		}
		return false;
	}
}