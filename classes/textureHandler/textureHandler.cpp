//
// Created by lenny on 21.01.2026.
//

#include "textureHandler.h++"

textureHandler::textureHandler() = default;

int textureHandler::getTextureLayer(const std::string& name) const {
    auto it = textureLayers.find(name);
    if (it == textureLayers.end())
        return -1;
    return it->second;
}


bool textureHandler::loadTextureFolder(const std::string& folderPath) {
    std::vector<SDL_Surface*> surfaces;

    for (auto& entry : fs::directory_iterator(folderPath)) {
        if (!entry.is_regular_file()) continue;

        SDL_Surface* surface = IMG_Load(entry.path().string().c_str());
        if (!surface) continue;

        if (surfaces.empty()) {
            texWidth = surface->w;
            texHeight = surface->h;
        } else {
            if (surface->w != texWidth || surface->h != texHeight) {
                SDL_DestroySurface(surface);
                continue;
            }
        }

        textureLayers[entry.path().stem().string()] = surfaces.size();
        surfaces.push_back(surface);
    }

    if (surfaces.empty())
        return false;

    layerCount = surfaces.size();

    glGenTextures(1, &textureArray);
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);

    glTexStorage3D(
        GL_TEXTURE_2D_ARRAY,
        1,
        GL_RGBA8,
        texWidth,
        texHeight,
        layerCount
    );

    for (int i = 0; i < layerCount; i++) {
        SDL_Surface* s = surfaces[i];

        GLenum format = (s->format->BytesPerPixel == 4)
            ? GL_RGBA
            : GL_RGB;

        glTexSubImage3D(
            GL_TEXTURE_2D_ARRAY,
            0,
            0, 0, i,
            texWidth,
            texHeight,
            1,
            format,
            GL_UNSIGNED_BYTE,
            s->pixels
        );

        SDL_DestroySurface(s);
    }

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    return true;
}

void textureHandler::bind(int unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureArray);
}


void textureHandler::cleanup() {
    if (textureArray) {
        glDeleteTextures(1, &textureArray);
        textureArray = 0;
    }
}

textureHandler::~textureHandler() {
    cleanup();
}
