//
// Created by lenny on 21.01.2026.
//

#include "textureHandler.h++"

#include <vector>
#include <algorithm>
#include <iostream>

VBND::textureHandler::textureHandler() = default;

VBND::textureHandler::~textureHandler() {
    cleanup();
}

bool VBND::textureHandler::loadTextureFolder(const std::string& folderPath) {
    cleanup();

    if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
        std::cerr << "Texture folder does not exist: " << folderPath << "\n";
        return false;
    }

    std::vector<fs::path> files;
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path());
        }
    }

    if (files.empty()) {
        std::cerr << "Texture folder is empty: " << folderPath << "\n";
        return false;
    }

    // Deterministic ordering
    std::sort(files.begin(), files.end());

    std::vector<SDL_Surface*> surfaces;
    surfaces.reserve(files.size());

    for (const auto& file : files) {
        SDL_Surface* loaded = IMG_Load(file.string().c_str());
        if (!loaded) {
            std::cerr << "Failed to load image: " << file
                      << " | " << SDL_GetError() << "\n";
            goto fail;
        }

        SDL_Surface* converted = SDL_ConvertSurfaceFormat(
            loaded,
            SDL_PIXELFORMAT_RGBA32
        );
        SDL_DestroySurface(loaded);

        if (!converted) {
            std::cerr << "Failed to convert image: " << file << "\n";
            goto fail;
        }

        surfaces.push_back(converted);
    }

    texWidth  = surfaces[0]->w;
    texHeight = surfaces[0]->h;
    layerCount = static_cast<int>(surfaces.size());

    // Validate sizes
    for (auto* s : surfaces) {
        if (s->w != texWidth || s->h != texHeight) {
            std::cerr << "Texture size mismatch in array\n";
            goto fail;
        }
    }

    // Create texture array
    glGenTextures(1, &textureArray);
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);

    glTexImage3D(
        GL_TEXTURE_2D_ARRAY,
        0,
        GL_RGBA8,
        texWidth,
        texHeight,
        layerCount,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        nullptr
    );

    for (int i = 0; i < layerCount; ++i) {
        glTexSubImage3D(
            GL_TEXTURE_2D_ARRAY,
            0,
            0, 0, i,
            texWidth,
            texHeight,
            1,
            GL_RGBA,
            GL_UNSIGNED_BYTE,
            surfaces[i]->pixels
        );

        textureLayers[files[i].stem().string()] = i;
    }

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

    for (auto* s : surfaces) {
        SDL_DestroySurface(s);
    }

    return true;

fail:
    for (auto* s : surfaces) {
        SDL_DestroySurface(s);
    }
    cleanup();
    return false;
}

int VBND::textureHandler::getTextureLayer(const std::string& name) const {
    auto it = textureLayers.find(name);
    if (it == textureLayers.end()) {
        return -1;
    }
    return it->second;
}

void VBND::textureHandler::bind(int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);
}

void VBND::textureHandler::cleanup() {
    if (textureArray) {
        glDeleteTextures(1, &textureArray);
        textureArray = 0;
    }

    textureLayers.clear();
    texWidth = texHeight = layerCount = 0;
}

