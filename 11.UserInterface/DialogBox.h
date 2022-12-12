#pragma once
#include "UIScreen.h"
#include <string>
#include <functional>

class DialogBox :public UIScreen
{
public:
	// (Lower draw order corresponds with further back)
	DialogBox(class Game* game, const std::string& text, std::function<void()> onOk);
	~DialogBox();
};
