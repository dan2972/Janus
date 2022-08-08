#include <glm/glm.hpp>
#include "actor.hpp"
#include "physics/collisions.hpp"

namespace Janus {
    void Actor::handleMovement() {
        lastPos = position;
        if (collidesWithActors) {
            for (auto obj : entityHandler->getList(GameObject::ACTOR)) {
                if (obj != this) {
                    handleCollision(obj);
                }
            }
        }

        position.x += velocity.x;
        position.y += velocity.y;
    }

    void Actor::handleCollision(GameObject* obj) {
        glm::vec4 broadPhaseBox = Collisions::GetSweptBroadPhaseBox({position, size}, velocity);

        colliding = false;
        if (Collisions::AABB(broadPhaseBox, {obj->getPos(), obj->getSize()})) {
            colliding = true;
            glm::vec2 normal;

            float contactTime = 0.0f;
            if (Collisions::SweptAABB({position, size}, velocity, {obj->getPos(), obj->getSize()}, normal, contactTime)) {
                if (collisionResponseType == CollisionResponseType::STOP) {
                    velocity = {0,0};
                } else if (collisionResponseType == CollisionResponseType::SLIDE) {
                    velocity += normal * glm::abs(velocity) * (1 - contactTime);
                }
            }
        }
    }
}