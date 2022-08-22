#ifndef JANUS_TEXTURE_MANAGER_HPP
#define JANUS_TEXTURE_MANAGER_HPP

#include <raylib.h>
#include <unordered_map>
#include <string>

namespace Janus {
    class TextureManager {
    public:
        static void Load(const std::string& path);
        static Texture2D* GetTexture(const std::string& path);

    private:
        static std::unordered_map<std::string, Texture2D> textures;
    };
}

#endif //JANUS_TEXTURE_MANAGER_HPP
