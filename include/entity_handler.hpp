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

        std::vector<GameObject*>& getList(GameObject::type type);

    private:
        void tick();

        std::vector<GameObject*> actorList;
        std::unordered_map<GameObject*, unsigned int> actorIndexMap;
        std::vector<GameObject*> toDelete;
    };
}

#endif //JANUS_ENTITY_HANDLER_HPP
