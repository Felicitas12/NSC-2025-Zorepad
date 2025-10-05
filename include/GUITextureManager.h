#pragma once
#include <string>
#include <unordered_map>

#include "Export.h"

struct GUITexture {
    unsigned int textureID;
    int width, height;

    GUITexture() : textureID(0), width(0), height(0) {}
    GUITexture(unsigned int id, int w, int h) : textureID(id), width(w), height(h) {}
};

// 9-slice info for scalable textures
struct NineSlice {
    float left, right, top, bottom;  // Границы в пикселях

    NineSlice(float l = 0, float r = 0, float t = 0, float b = 0)
        : left(l), right(r), top(t), bottom(b) {
    }
};

// Менеджер текстур GUI
class GUITextureManager {
private:
    std::unordered_map<std::string, GUITexture> textures;
    std::unordered_map<std::string, NineSlice> nineSlices;

public:
    ENGINE_API void addTexture(const std::string& name, unsigned int textureID, int width, int height);
	ENGINE_API void addTexture(const std::string& name, GUITexture texture);

    ENGINE_API void addNineSlice(const std::string& name, const NineSlice& slice);

    ENGINE_API GUITexture* getTexture(const std::string& name);

    ENGINE_API NineSlice* getNineSlice(const std::string& name);

    ENGINE_API bool hasTexture(const std::string& name);
};