#ifndef JANUS_TILEMAP_HPP
#define JANUS_TILEMAP_HPP

#include <unordered_map>
#include <string>
#include "tile.hpp"
#include "chunk.hpp"

namespace Janus {
    class Tilemap {
    public:
        Tilemap() = default;
        ~Tilemap() {
            for (auto& it : chunkMap) {
                delete it.second;
            }
        }

        void addChunk(Chunk* chunk) {
            chunkMap.insert({std::to_string(chunk->getChunkX()) + "," + std::to_string(chunk->getChunkY()), chunk});
        }

        void tickChunk(int chunkX, int chunkY) {
            getChunk(chunkX, chunkY)->tick();
        }

        void renderChunk(int chunkX, int chunkY, float dt) {
            getChunk(chunkX, chunkY)->render(dt);
        }

        //renders the chunks around the chunk located at centerX and centerY with a given radius
        void renderChunkAroundCoord(int centerX, int centerY, int radius, float dt) {
            for (int i = centerY - radius; i <= centerY + radius; ++i) {
                for (int j = centerX - radius; j <= centerX + radius; ++j) {
                    Chunk* chunk = getChunk(j, i);
                    if (chunk != nullptr) chunk->render(dt);
                }
            }
        }

        bool chunkExistsAt(int chunkX, int chunkY) {
            std::string key = std::to_string(chunkX) + "," + std::to_string(chunkY);
            auto it = chunkMap.find(key);
            if (it != chunkMap.end()) {
                return true;
            }
            return false;
        }

        Chunk* getChunk(int chunkX, int chunkY) {
            std::string key = std::to_string(chunkX) + "," + std::to_string(chunkY);
            auto it = chunkMap.find(key);
            if (it != chunkMap.end()) {
                return chunkMap.at(key);
            }
            return nullptr;
        }

        std::unordered_map<std::string, Chunk*>& getChunkMap(){
            return chunkMap;
        }
    private:
        std::unordered_map<std::string, Chunk*> chunkMap;
    };
}

#endif //JANUS_TILEMAP_HPP
