#ifndef JANUS_ENTITY_RENDERER_HPP
#define JANUS_ENTITY_RENDERER_HPP

#include "tilemap.hpp"
#include "game_object.hpp"

namespace Janus {
    class EntityRenderer {
    public:
        explicit EntityRenderer(Tilemap* tilemap) : tilemap{tilemap} {}

        void renderActors(const std::vector<GameObject*>& actorList, float dt);
        void renderTilemap(int centerX, int centerY, int radius, float dt);
        void renderProjectiles();
        void renderParticles();
    private:
        Tilemap* tilemap = nullptr;
    };
}

#endif //JANUS_ENTITY_RENDERER_HPP
