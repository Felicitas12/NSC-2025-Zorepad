#pragma once
#include "GUIScreen.h"
#include "Label.h"
#include "ScreenDispatcher.h"
#include "TexturedButton.h"
#include "TexturedPanel.h"

class MainMenuScreen : public GUIScreen
{
private:
	ScreenDispatcher* screenManager = nullptr;
public:
	void setScreenManager(ScreenDispatcher* manager) {
		screenManager = manager;
	}

	void onCreate() override {



		auto overlay = std::make_shared<TexturedPanel>(0, 0, 1920, 1080);
		overlay->style.backgroundTexture = "mainmenu_background";



		float screenWidth = 1920.0f;
		float screenHeight = 1080.0f;

		float buttonWidth = 380.0f;
		float buttonHeight = 150.0f;

		// Центр по X
		float buttonX = (screenWidth - buttonWidth) / 2.0f;

		// На 15% от нижнего края
		float buttonY = screenHeight * 0.15f; // примерно 162 пикселя от низа

		auto startButton = std::make_shared<TexturedButton>(buttonX, buttonY, buttonWidth, buttonHeight, "");
		startButton->setOnClick([this]() {
			if (screenManager) {
				screenManager->popScreen();
				screenManager->pushScreen("warning");
			}
			});

		startButton->style.normalTexture = "mainmenu_button";
		startButton->style.hoverTexture = "mainmenu_button_hover";

		addElement(overlay);
		addElement(startButton);


		blockInput = true;
	}
	bool handleKeyboard(int key, bool pressed) override {



		return true;
	}

};
