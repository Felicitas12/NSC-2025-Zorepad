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


		auto titleLabel = std::make_shared<Label>(180, 720, 190, 74, "Menu");
		titleLabel->style.textColor = { 0.0f, 0.0f, 0.0f, 1.0f };
		titleLabel->style.alignment = Label::Style::CENTER;

		auto closeButton = std::make_shared<TexturedButton>(180, 620, 190, 74, "");
		closeButton->setOnClick([this]() {
			if (screenManager) {
				screenManager->popScreen();
			}
			});

		closeButton->style.normalTexture = "mainmenu_button";
		closeButton->style.hoverTexture = "mainmenu_button_hover";

		addElement(titleLabel);
		addElement(overlay);
		addElement(closeButton);


		blockInput = true; // Ѕлокируем ввод дл¤ экранов ниже
	}
	bool handleKeyboard(int key, bool pressed) override {



		return true;
	}

};
