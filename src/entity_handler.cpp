#include "entity_handler.hpp"

namespace Janus {
    EntityHandler::~EntityHandler() {
        for (auto obj : actorList) {
            delete obj;
        }
        for (auto obj : projectileList) {
            delete obj;
        }
        for (auto obj : particleList) {
            delete obj;
        }
    }

    void EntityHandler::add(GameObject *obj) {
        toAdd.push_back(obj);
    }

    void EntityHandler::remove(GameObject* obj) {
        toDelete.push_back(obj);
    }

    void EntityHandler::update() {

        for (auto obj : toDelete) {
            switch (obj->getType()) {
                case GameObject::Type::ACTOR:
                    removeObjFromList(obj, actorList);
                    break;
                case GameObject::Type::PROJECTILE:
                    removeObjFromList(obj, projectileList);
                    break;
                case GameObject::Type::PARTICLE:
                    removeObjFromList(obj, particleList);
                    break;
                default:
                    removeObjFromList(obj, actorList);
                    break;
            }

            delete obj;
        }
        toDelete.clear();

        for (auto obj : toAdd) {
            switch (obj->getType()) {
                case GameObject::Type::ACTOR:
                    addObjToList(obj, actorList);
                    break;
                case GameObject::Type::PROJECTILE:
                    addObjToList(obj, projectileList);
                    break;
                case GameObject::Type::PARTICLE:
                    addObjToList(obj, particleList);
                    break;
                default:
                    addObjToList(obj, actorList);
                    break;
            }
        }
        toAdd.clear();

        tick();
    }

    void EntityHandler::tick() {
        for (auto & obj : projectileList) {
            obj->tick();
        }
        for (auto & obj : particleList) {
            obj->tick();
        }
        for (auto & obj : actorList) {
            obj->tick();
        }
    }

    void EntityHandler::render(int centerChunkPosX, int centerChunkPosY, float dt) {
        tilemap.renderChunkAroundCoord(centerChunkPosX, centerChunkPosY, 1, dt);
        for (auto & obj : projectileList) {
            obj->render(dt);
        }
        for (auto & obj : particleList) {
            obj->render(dt);
        }
        for (auto & obj : actorList) {
            obj->render(dt);
        }
    }

    void EntityHandler::removeObjFromList(GameObject* obj, std::vector<GameObject*>& list) {
        if (obj != list.back()) {
            objIndexMap.at(list.back()) = objIndexMap.at(obj);
            std::swap(list[objIndexMap.at(obj)], list.back());
        }
        list.pop_back();
        objIndexMap.erase(obj);
    }

    void EntityHandler::addObjToList(GameObject* obj, std::vector<GameObject*>& list) {
        objIndexMap.insert({obj, list.size()});
        list.push_back(obj);
    }

    std::vector<GameObject*>& EntityHandler::getList(GameObject::Type type) {
        switch (type) {
            case GameObject::Type::ACTOR:
                return this->actorList;
            case GameObject::Type::PROJECTILE:
                return this->projectileList;
            case GameObject::Type::PARTICLE:
                return this->particleList;
            default:
                return this->actorList;
        }
    }

    Tilemap &EntityHandler::getTileMap() {
        return tilemap;
    }
}
