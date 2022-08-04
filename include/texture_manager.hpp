#ifndef JANUS_TEXTURE_MANAGER_HPP
#define JANUS_TEXTURE_MANAGER_HPP

#include <raylib-cpp.hpp>
#include <unordered_map>
#include <string>

namespace Janus {
    class TextureManager {
    public:
        static void loadTexture(const std::string& path);
        static raylib::Texture2D* getTexture(const std::string& path);

    private:
        static std::unordered_map<std::string, raylib::Texture2D> textures;
    };
}

#endif //JANUS_TEXTURE_MANAGER_HPP
