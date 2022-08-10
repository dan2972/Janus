#ifndef JANUS_ENTITY_HANDLER_HPP
#define JANUS_ENTITY_HANDLER_HPP

#include <vector>
#include <unordered_map>
#include <queue>
#include "game_object.hpp"
#include "tilemap.hpp"
#include "entity_renderer.hpp"

namespace Janus {
    class EntityHandler {
    public:
        EntityHandler() = default;
        ~EntityHandler();

        void add(GameObject* obj);
        void remove(GameObject* obj);

        void update();
        void render(int centerChunkPosX, int centerChunkPosY, float dt);

        std::vector<GameObject*>& getList(GameObject::Type type);
        Tilemap& getTileMap();

    private:
        void tick();

        Tilemap tilemap;
        EntityRenderer entityRenderer{&tilemap};

        std::vector<GameObject*> actorList;
        std::vector<GameObject*> projectileList;
        std::vector<GameObject*> particleList;
        std::unordered_map<GameObject*, unsigned int> objIndexMap;
        std::queue<GameObject*> toDelete;
        std::queue<GameObject*> toAdd;

        void removeObjFromList(GameObject* obj, std::vector<GameObject*>& list);
        void addObjToList(GameObject* obj, std::vector<GameObject*>& list);
    };
}

#endif //JANUS_ENTITY_HANDLER_HPP
