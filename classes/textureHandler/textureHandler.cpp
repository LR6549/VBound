//
// Created by lenny on 21.01.2026.
//

#include "textureHandler.h++"

bool textureHandler::existsTexture(const std::string& textureName) const {
    if (textureMap.contains(textureName)) {
        return true;
    } return false;
}

SDL_Texture* textureHandler::getTexture(const std::string& textureName) {
    if (existsTexture(textureName)) {
        return textureMap[textureName];
    }
    return nullptr;
}

bool textureHandler::loadTexturesFromFolder(const std::string& textureFolder, const std::string& textureName, SDL_Renderer* renderer) {
    if (!fs::exists(textureFolder)) {
        JFLX::log("Texture folder does not exist: ", textureFolder, JFLX::LOGTYPE::JFLX_INFO);
        return false;
    }

    for (const auto& dir : fs::recursive_directory_iterator(textureFolder)) {
        if (dir.is_regular_file() && dir.path().extension() == ".png") {
            std::string tempPath = dir.path().string();
            std::string tempName = dir.path().stem().string();

            JFLX::log("Texture: ", (tempName.append(" in ").append(tempPath)), JFLX::LOGTYPE::JFLX_INFO);

            //+ load Texture from file
            SDL_Texture* tex = IMG_LoadTexture(renderer, tempPath.c_str());
            if (!tex) {
                JFLX::log("Failed to load texture: ", SDL_GetError(), JFLX::LOGTYPE::JFLX_ERROR);
                continue;
            }

            textureMap[tempName] = tex;
            JFLX::log("Loaded Texture: ", (tempPath.append(" in ").append(tempName)), JFLX::LOGTYPE::JFLX_SUCCESS);
        }
    }

    return true;
}

void textureHandler::cleanUp() {
    for (const auto &[fst, snd] : textureMap) {
        SDL_DestroyTexture(snd);
        JFLX::log("Cleared Texture: ", fst, JFLX::LOGTYPE::JFLX_SUCCESS);
    }
    textureMap.clear();
    JFLX::log("Finished: ", "textureHandler Clear Up", JFLX::LOGTYPE::JFLX_SUCCESS);
}