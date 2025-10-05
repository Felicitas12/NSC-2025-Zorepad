#pragma once
#include "ScreenDispatcher.h"

class WarningScreen
{
private:
	ScreenDispatcher* screenManager = nullptr;
public:
	void setScreenManager(ScreenDispatcher* manager) {
		screenManager = manager;
	}
};
