#pragma once
class GUITextureManager;
class GUIRenderer;

class GUIElement {
public:
    float x, y, width, height;
    bool visible = true;
    bool enabled = true;

    GUIElement(float x, float y, float width, float height)
        : x(x), y(y), width(width), height(height) {
    }

    virtual ~GUIElement() = default;
    virtual void render(GUIRenderer& renderer, GUITextureManager& textureManager) = 0;
    // Теперь передаем и клик (момент нажатия), и состояние мыши (нажата ли кнопка)
    virtual bool handleMouse(float mouseX, float mouseY, bool clicked, bool mousePressed) { return false; }
    virtual void update(float deltaTime) {}

    bool isPointInside(float px, float py) const {
        return px >= x && px <= x + width && py >= y && py <= y + height;
    }

    void setPosition(float newX, float newY) { x = newX; y = newY; }
    void setSize(float newWidth, float newHeight) { width = newWidth; height = newHeight; }
};