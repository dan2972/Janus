#include <iostream>
#include "texture_manager.hpp"

namespace Janus {
    std::unordered_map<std::string, raylib::Texture2D> TextureManager::textures;

    void TextureManager::loadTexture(const std::string &path) {
        textures.insert({path, raylib::Texture2D(path)});
    }
    raylib::Texture2D* TextureManager::getTexture(const std::string &path) {
        raylib::Texture2D texture;
        auto it = textures.find(path);
        if (it != textures.end()) {
            return &textures.at(path);
        }
        std::cerr << "Texture " + path + " has not been loaded" << std::endl;
        return nullptr;
    }
}