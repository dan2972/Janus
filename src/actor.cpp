#include <iostream>
#include "actor.hpp"
#include "physics/collisions.hpp"

namespace Janus {
    void Actor::handleMovement(float deltaTime) {
        if (collidesWithActors) {
            for (auto obj : entityHandler->getList(GameObject::ACTOR)) {
                if (obj != this) {
                    handleCollision(obj, deltaTime);
                }
            }
        }

        if (!colliding) {
            position.x += velocity.x * deltaTime;
            position.y += velocity.y * deltaTime;
        }
    }

    void Actor::handleCollision(GameObject* obj, float deltaTime) {
        glm::vec4 broadPhaseBox = Collisions::GetSweptBroadPhaseBox({position, size}, velocity * deltaTime);

        colliding = false;
        if (Collisions::AABB(broadPhaseBox, {obj->getPos(), obj->getSize()})) {
            colliding = true;
            glm::vec2 normal;
            float collisionTime = Collisions::SweptAABB({position, size}, velocity * deltaTime, {obj->getPos(), obj->getSize()}, normal);
            position.x += velocity.x * collisionTime * deltaTime;
            position.y += velocity.y * collisionTime * deltaTime;

            if (collisionTime < 1) {
                if (collisionResponseType == CollisionResponseType::STOP) {
                    velocity.x = 0;
                    velocity.y = 0;
                }
                if (collisionResponseType == CollisionResponseType::SLIDE) {
                    float remainingTime = 1 - collisionTime;
                    float dotProd = (velocity.x * normal.y + velocity.y * normal.x) * remainingTime;
                    velocity.x = dotProd * normal.y;
                    velocity.y = dotProd * normal.x;
                }
                position.x += velocity.x * deltaTime;
                position.y += velocity.y * deltaTime;
            }
        }
    }
}