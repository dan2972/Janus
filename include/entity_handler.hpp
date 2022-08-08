#ifndef JANUS_ENTITY_HANDLER_HPP
#define JANUS_ENTITY_HANDLER_HPP

#include <vector>
#include <unordered_map>
#include "game_object.hpp"

namespace Janus {
    class EntityHandler {
    public:
        EntityHandler() = default;
        ~EntityHandler();

        void add(GameObject* obj);
        void remove(GameObject* obj);

        void update();
        void render(float dt);

        std::vector<GameObject*>& getList(GameObject::Type type);

    private:
        void tick();

        std::vector<GameObject*> actorList;
        std::vector<GameObject*> projectileList;
        std::vector<GameObject*> particleList;
        std::unordered_map<GameObject*, unsigned int> objIndexMap;
        std::vector<GameObject*> toDelete;
        std::vector<GameObject*> toAdd;

        void removeObjFromList(GameObject* obj, std::vector<GameObject*>& list);
        void addObjToList(GameObject* obj, std::vector<GameObject*>& list);
    };
}

#endif //JANUS_ENTITY_HANDLER_HPP
