#pragma once

#include <glm/vec4.hpp>
#include <string>

#include "Export.h"
#include "GUIElement.h"
#include "memory"

struct NineSlice;
struct GUITexture;

class TexturedPanel : public GUIElement {
private:
    std::vector<std::shared_ptr<GUIElement>> children;

public:
    struct Style {
        std::string backgroundTexture = "panel_bg";
        glm::vec4 tint = { 1.0f, 1.0f, 1.0f, 1.0f };
        bool useNineSlice = true;
        bool drawBackground = true;
    } style;

    ENGINE_API TexturedPanel(float x, float y, float width, float height);

    ENGINE_API void addChild(std::shared_ptr<GUIElement> child);

    ENGINE_API void removeChild(std::shared_ptr<GUIElement> child);

    ENGINE_API void render(GUIRenderer& renderer, GUITextureManager& textureManager) override;

    ENGINE_API bool handleMouse(float mouseX, float mouseY, bool clicked, bool mousePressed) override;

    ENGINE_API void update(float deltaTime) override;

    ENGINE_API const std::vector<std::shared_ptr<GUIElement>>& getChildren();
};
