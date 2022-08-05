#include <iostream>
#include "entity_handler.hpp"

namespace Janus {
    EntityHandler::~EntityHandler() {
        for (auto obj : actorList) {
            delete obj;
        }
    }

    void EntityHandler::add(GameObject *obj) {
        actorIndexMap.insert({obj, actorList.size()});
        actorList.push_back(obj);
    }

    void EntityHandler::remove(GameObject* obj) {
        toDelete.push_back(obj);
    }

    void EntityHandler::update(float deltaTime) {

        for (auto obj : toDelete) {
            if (obj != actorList.back()) {
                actorIndexMap.at(actorList.back()) = actorIndexMap.at(obj);
                std::swap(actorList[actorIndexMap.at(obj)], actorList.back());
            }
            actorList.pop_back();
            actorIndexMap.erase(obj);
            delete obj;
        }
        toDelete.clear();

        tick(deltaTime);
        render();
    }

    void EntityHandler::tick(float deltaTime) {
        for (auto & obj : actorList) {
            obj->tick(deltaTime);
        }
    }

    void EntityHandler::render() {
        for (auto & obj : actorList) {
            obj->render();
        }
    }

    std::vector<GameObject*>& EntityHandler::getList(GameObject::type type) {
        switch (type) {
            case GameObject::type::ACTOR:
                return this->actorList;
            default:
                return this->actorList;
        }
    }
}
