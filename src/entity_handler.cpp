#include "entity_handler.hpp"
#include "actor.hpp"

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
        toAdd.push(obj);
    }

    void EntityHandler::remove(GameObject* obj) {
        toDelete.push(obj);
    }

    void EntityHandler::update() {
        while (!toDelete.empty()) {
            auto obj = toDelete.front();
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
            toDelete.pop();
        }

        while (!toAdd.empty()) {
            auto obj = toAdd.front();
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
            toAdd.pop();
        }

        tick();
    }

    void EntityHandler::tick() {
        tilemap.clearRandomTickList();
        for (auto & obj : projectileList) {
            obj->tick();
        }
        for (auto & obj : particleList) {
            obj->tick();
        }
        for (auto & obj : actorList) {
            obj->tick();
            auto actor = (Actor*) obj;
            if (actor->getActorType() == Actor::ActorType::PLAYER) {
                tilemap.addChunksToRandomTickList((int)actor->getChunkPos().x, (int)actor->getChunkPos().y, 1);
            }
        }
        tilemap.tick();
        tilemap.randomTick(1);
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
