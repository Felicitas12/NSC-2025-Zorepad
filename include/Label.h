#pragma once
#include <string>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "Export.h"
#include "GUIElement.h"
#include "GUIScreen.h"



struct GUITexture;

class ENGINE_API Label : public GUIElement {
private:
    std::string text;

public:
    struct Style {
        glm::vec4 textColor = { 1.0f, 1.0f, 1.0f, 1.0f };
        std::string backgroundTexture = "";
        glm::vec4 backgroundTint = { 1.0f, 1.0f, 1.0f, 1.0f };
        bool drawBackground = false;
        enum Alignment { LEFT, CENTER, RIGHT } alignment = CENTER;
    } style;

    Label(float x, float y, float width, float height, const std::string& text);
    void setText(const std::string& newText);
    void render(GUIRenderer& renderer, GUITextureManager& textureManager) override;
    std::string& getText();
    glm::vec4& getTextColor();
    glm::vec2 getTextPosition();
    Style::Alignment getAlignment();
};