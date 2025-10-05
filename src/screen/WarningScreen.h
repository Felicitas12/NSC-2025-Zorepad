#pragma once
#include "Label.h"
#include "ScreenDispatcher.h"
#include "TexturedButton.h"
#include "TexturedPanel.h"

class WarningScreen : public GUIScreen
{
private:
	ScreenDispatcher* screenManager = nullptr;
public:
	void setScreenManager(ScreenDispatcher* manager) {
		screenManager = manager;
	}
	void onCreate() override {



		auto overlay = std::make_shared<TexturedPanel>(0, 0, 1920, 1080);
		overlay->style.backgroundTexture = "warning_background";


		auto indoor_button = std::make_shared<TexturedButton>(300, 150, 380, 150, "");
		indoor_button->setOnClick([this]() {
			if (screenManager) {

				screenManager->popScreen();
			}
			});
		indoor_button->style.normalTexture = "indoor_button";
		indoor_button->style.hoverTexture = "indoor_button_hover";


		auto outdoor_button = std::make_shared<TexturedButton>(1300, 150, 380, 150, "");
		outdoor_button->setOnClick([this]() {
			if (screenManager) {

				screenManager->popScreen();
			}
			});
		outdoor_button->style.normalTexture = "outdoor_button";
		outdoor_button->style.hoverTexture = "outdoor_button_hover";

		addElement(overlay);
		addElement(indoor_button);
		addElement(outdoor_button);


		blockInput = true;
	}
	bool handleKeyboard(int key, bool pressed) override {



		return true;
	}
};
