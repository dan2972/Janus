#ifndef JANUS_ENTITY_HANDLER_HPP
#define JANUS_ENTITY_HANDLER_HPP

#include <vector>
#include <unordered_map>
#include <queue>
#include "game_object.hpp"
#include "tilemap.hpp"
#include "entity_renderer.hpp"
#include "game_camera.hpp"

namespace Janus {
    class EntityHandler {
    public:
        EntityHandler() = default;

        void add(GameObject* obj);
        void remove(GameObject& obj);

        void update();
        void render(GameCamera& camera, int centerChunkPosX, int centerChunkPosY, float dt);
        void loadChunks(int centerChunkPosX, int centerChunkPosY, int radius);
        void preloadTilemapTextures(GameCamera& camera, int centerChunkPosX, int centerChunkPosY);

        std::vector<std::unique_ptr<GameObject>>& getList(GameObject::Type type);
        Tilemap& getTileMap();

    private:
        void tick();

        Tilemap tilemap;
        EntityRenderer entityRenderer{&tilemap};

        std::vector<std::unique_ptr<GameObject>> actorList;
        std::vector<std::unique_ptr<GameObject>> projectileList;
        std::vector<std::unique_ptr<GameObject>> particleList;
        std::unordered_map<GameObject*, unsigned int> objIndexMap;
        std::queue<std::reference_wrapper<GameObject>> toDelete;
        std::queue<std::unique_ptr<GameObject>> toAdd;

        void removeObjFromList(GameObject& obj, std::vector<std::unique_ptr<GameObject>>& list);
        void addObjToList(std::unique_ptr<GameObject> obj, std::vector<std::unique_ptr<GameObject>>& list);
    };
}

#endif //JANUS_ENTITY_HANDLER_HPP
