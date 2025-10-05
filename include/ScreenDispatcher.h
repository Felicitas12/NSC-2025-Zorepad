#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <stack>

#include "GUIScreen.h"
#include "Window.h"


class GUITextureManager;

class ScreenDispatcher {
private:
    std::unordered_map<std::string, std::shared_ptr<GUIScreen>> screens;
    std::stack<std::string> screenStack;
    std::string currentScreen;

public:
    // Регистрируем экран
    ENGINE_API void registerScreen(const std::string& name, std::shared_ptr<GUIScreen> screen);

    // Показать экран (заменяет текущий)
    ENGINE_API void showScreen(const std::string& name);

    // Открыть экран поверх текущего (модальное окно)
    ENGINE_API void pushScreen(const std::string& name);

    // Закрыть верхний экран
    ENGINE_API void popScreen();

    // Закрыть до определенного экрана
    ENGINE_API void popToScreen(const std::string& name);

    // Скрыть все экраны
    ENGINE_API void hideAll();

    // Получить текущий верхний экран
    ENGINE_API std::shared_ptr<GUIScreen> getCurrentScreen();

    // НОВЫЕ МЕТОДЫ для правильного рендеринга:

    // Получить экран по имени
    ENGINE_API std::shared_ptr<GUIScreen> getScreen(const std::string& name);

    // Получить копию стека экранов
    ENGINE_API std::stack<std::string> getScreenStack() const;

    // Получить список всех активных экранов (снизу вверх)
    ENGINE_API std::vector<std::string> getActiveScreens() const;

    // Проверить, открыт ли экран
    ENGINE_API bool isScreenActive(const std::string& name);

    void render(GUIRenderer& renderer, GUITextureManager& textureManager);

    bool handleMouse(float mouseX, float mouseY, bool clicked, bool mousePressed);

    bool handleKeyboard(int key, bool pressed);

    void update(float deltaTime);
};