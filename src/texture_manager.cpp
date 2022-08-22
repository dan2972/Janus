#include "texture_manager.hpp"
#include <iostream>

namespace Janus {
    std::unordered_map<std::string, Texture2D> TextureManager::textures;

    void TextureManager::Load(const std::string &path) {
        textures.insert({path, LoadTexture(path.c_str())});
    }

    Texture2D* TextureManager::GetTexture(const std::string &path) {
        Texture2D texture;
        auto it = textures.find(path);
        if (it != textures.end()) {
            return &textures.at(path);
        }
        std::cerr << "Texture " + path + " has not been loaded" << std::endl;
        return nullptr;
    }
}