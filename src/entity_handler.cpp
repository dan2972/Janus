#include "entity_handler.hpp"
#include "actor.hpp"
#include "global_values.hpp"

namespace Janus {
    void EntityHandler::add(GameObject* obj) {
        toAdd.push(std::unique_ptr<GameObject>(obj));
    }

    void EntityHandler::remove(GameObject& obj) {
        toDelete.push(std::ref(obj));
    }

    void EntityHandler::update() {
        while (!toDelete.empty()) {
            auto obj = toDelete.front();
            switch (obj.get().getType()) {
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
            toDelete.pop();
        }

        while (!toAdd.empty()) {
            auto& obj = toAdd.front();
            switch (obj->getType()) {
                case GameObject::Type::ACTOR:
                    addObjToList(std::move(obj), actorList);
                    break;
                case GameObject::Type::PROJECTILE:
                    addObjToList(std::move(obj), projectileList);
                    break;
                case GameObject::Type::PARTICLE:
                    addObjToList(std::move(obj), particleList);
                    break;
                default:
                    addObjToList(std::move(obj), actorList);
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
            auto& actor = (Actor&) obj;
            if (actor.getActorType() == Actor::ActorType::PLAYER) {
                tilemap.addChunksToRandomTickList((int)actor.getChunkPos().x, (int)actor.getChunkPos().y, 1);
            }
        }
        tilemap.tick();
        tilemap.randomTick(1);
    }

    void EntityHandler::render(int centerChunkPosX, int centerChunkPosY, float dt) {
        entityRenderer.renderTilemap(centerChunkPosX, centerChunkPosY, CHUNK_RENDER_DISTANCE, dt);
        entityRenderer.renderActors(actorList, dt);
    }

    void EntityHandler::removeObjFromList(GameObject& obj, std::vector<std::unique_ptr<GameObject>>& list) {
        if (&obj != list.back().get()) {
            objIndexMap.at(list.back().get()) = objIndexMap.at(&obj);
            std::swap(list[objIndexMap.at(&obj)], list.back());
        }
        list.pop_back();
        objIndexMap.erase(&obj);
    }

    void EntityHandler::addObjToList(std::unique_ptr<GameObject> obj, std::vector<std::unique_ptr<GameObject>>& list) {
        objIndexMap.insert({obj.get(), list.size()});
        list.push_back(std::move(obj));
    }

    std::vector<std::unique_ptr<GameObject>>& EntityHandler::getList(GameObject::Type type) {
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
