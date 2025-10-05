#pragma once
#include <memory>
#include <vector>

#include "Export.h"


class GUITextureManager;
class GUIRenderer;
class GUIElement;

class GUIScreen {
protected:
    std::vector<std::shared_ptr<GUIElement>> elements;
    bool visible = false;
    bool blockInput = true; // Блокирует ли ввод для экранов ниже

public:
    ENGINE_API virtual ~GUIScreen() = default;

    ENGINE_API virtual void onCreate() {} // Вызывается при создании экрана
    ENGINE_API virtual void onShow() {}   // Вызывается при показе экрана
    ENGINE_API virtual void onHide() {}   // Вызывается при скрытии экрана
    ENGINE_API virtual void onUpdate(float deltaTime) {}

    ENGINE_API void addElement(std::shared_ptr<GUIElement> element);
    ENGINE_API void removeElement(std::shared_ptr<GUIElement> element);

    ENGINE_API void render(GUIRenderer& renderer, GUITextureManager& textureManager);
    ENGINE_API bool handleMouse(float mouseX, float mouseY, bool clicked, bool mousePressed);
    ENGINE_API virtual bool handleKeyboard(int key, bool pressed);

    ENGINE_API void setVisible(bool vis);
    ENGINE_API bool isVisible() const;

    ENGINE_API void setBlockInput(bool block);
    ENGINE_API bool doesBlockInput() const;

    ENGINE_API const std::vector<std::shared_ptr<GUIElement>>& getElements() const;


};