//
// Created by lenny on 21.01.2026.
//

#ifndef VBOUND_TEXTUREHANDLER_H
#define VBOUND_TEXTUREHANDLER_H

#include <iostream>
#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <JFLX/logging.hpp>
#include <SDL3/SDL.h>
#include <SDL3/SDL3_image/SDL_image.h>

namespace fs = std::filesystem;


class textureHandler {
private:
    std::unordered_map<std::string, SDL_Texture*> textureMap;

public:
    textureHandler();
    ~textureHandler();

    bool existsTexture(const std::string& textureName) const;

    SDL_Texture* getTexture(const std::string& textureName);

    bool loadTexturesFromFolder(const std::string& textureFolder, const std::string& textureName, SDL_Renderer* renderer);

    void cleanUp();
};


#endif //VBOUND_TEXTUREHANDLER_H