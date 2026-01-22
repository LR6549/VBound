//
// Created by lenny on 21.01.2026.
//

#ifndef VBOUND_TEXTUREHANDLER_H
#define VBOUND_TEXTUREHANDLER_H

#include <unordered_map>
#include <string>
#include <filesystem>
#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL3_image/SDL_image.h>

namespace fs = std::filesystem;

class textureHandler {
private:
    GLuint textureArray = 0;
    int texWidth = 0;
    int texHeight = 0;
    int layerCount = 0;

    std::unordered_map<std::string, int> textureLayers;

public:
    textureHandler();
    ~textureHandler();

    bool loadTextureFolder(const std::string& folderPath);

    int getTextureLayer(const std::string& name) const;

    [[nodiscard]] GLuint getTextureArray() const { return textureArray; }

    void bind(int unit = 0) const;

    void cleanup();
};

#endif // VBOUND_TEXTUREHANDLER_H
