#ifndef JANUS_ENTITY_RENDERER_HPP
#define JANUS_ENTITY_RENDERER_HPP

#include "tilemap.hpp"
#include "game_object.hpp"

namespace Janus {
    class EntityRenderer {
    public:
        explicit EntityRenderer(Tilemap* tilemap) : tilemap{tilemap} {}

        void renderActors(const std::vector<std::unique_ptr<GameObject>>& actorList, float dt);
        void renderTilemap(int centerX, int centerY, int radius, float dt);
        void renderProjectiles();
        void renderParticles();
    private:
        void drawTile(Tile& tile);

        Tilemap* tilemap = nullptr;
    };
}

#endif //JANUS_ENTITY_RENDERER_HPP
