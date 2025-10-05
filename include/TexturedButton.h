#pragma once
#include <string>
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>
#include "Export.h"

#include "GUIElement.h"

struct NineSlice;
struct GUITexture;

class ENGINE_API TexturedButton : public GUIElement {
private:
    std::string text;
    std::function<void()> onClick;
    bool isPressed = false;
    bool isHovered = false;

public:
    struct Style {
        std::string normalTexture = "button_normal";
        std::string hoverTexture = "button_hover";
        std::string pressedTexture = "button_pressed";
        std::string disabledTexture = "button_disabled";
        glm::vec4 tint = { 1.0f, 1.0f, 1.0f, 1.0f };
        glm::vec4 textColor = { 1.0f, 1.0f, 1.0f, 1.0f };
        bool useNineSlice = true;
    } style;

    TexturedButton(float x, float y, float width, float height, const std::string& text);

    void setOnClick(std::function<void()> callback);

    void setText(const std::string& newText);

    void render(GUIRenderer& renderer, GUITextureManager& textureManager) override;

    bool handleMouse(float mouseX, float mouseY, bool clicked, bool mousePressed) override;

    std::string& getText();
    glm::vec4& getTextColor();

    glm::vec2 getTextPosition();
};
