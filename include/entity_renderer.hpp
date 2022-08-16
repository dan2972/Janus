#ifndef JANUS_ENTITY_RENDERER_HPP
#define JANUS_ENTITY_RENDERER_HPP

#include "tilemap.hpp"
#include "game_object.hpp"
#include "game_camera.hpp"

namespace Janus {
    class EntityRenderer {
    public:
        EntityRenderer() = default;
        explicit EntityRenderer(Tilemap* tilemap) : tilemap{tilemap} {}

        void renderActors(const std::vector<std::unique_ptr<GameObject>>& actorList, float dt);
        void renderTilemap(GameCamera& camera, int centerX, int centerY, int radius, float dt);
        void preloadTilemapTextures(GameCamera& camera, int centerX, int centerY, int radius);
        void renderProjectiles();
        void renderParticles();
    private:
        Tilemap* tilemap = nullptr;
        std::queue<std::reference_wrapper<Chunk>> chunkRenderQueue;
    };
}

#endif //JANUS_ENTITY_RENDERER_HPP
