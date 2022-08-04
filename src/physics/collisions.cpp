#include <limits>
#include <algorithm>
#include "physics/collisions.hpp"

namespace Janus {
    // Simple AABB collision using two boxes
    bool Collisions::AABB(glm::vec4 b1, glm::vec4 b2) {
        return !(b1.x + b1.z < b2.x || b1.x > b2.x + b2.z || b1.y + b1.w < b2.y || b1.y > b2.y + b2.w);
    }

    // Calculates the collision time using swept AABB with moving box 1 and stationary box 2
    // Takes in empty normals to output onto
    float Collisions::SweptAABB(glm::vec4 box1, glm::vec2 velocity, glm::vec4 box2, glm::vec2& normal) {
        glm::vec2 invEntry;
        glm::vec2 invExit;

        if (velocity.x > 0) {
            invEntry.x = box2.x - (box1.x + box1.z);
            invExit.x = (box2.x + box2.z) - box1.x;
        } else {
            invEntry.x = (box2.x + box2.z) - box1.x;
            invExit.x = box2.x - (box1.x + box1.z);
        }

        if (velocity.y > 0) {
            invEntry.y = box2.y - (box1.y + box1.w);
            invExit.y = (box2.y + box2.w) - box1.y;
        } else {
            invEntry.y = (box2.y + box2.w) - box1.y;
            invExit.y = box2.y - (box1.y + box1.w);
        }

        glm::vec2 entry;
        glm::vec2 exit;

        if (velocity.x == 0) {
            entry.x = -std::numeric_limits<float>::infinity();
            exit.x = std::numeric_limits<float>::infinity();
        } else {
            entry.x = invEntry.x / velocity.x;
            exit.x = invExit.x / velocity.x;
        }

        if (velocity.y == 0) {
            entry.y = -std::numeric_limits<float>::infinity();
            exit.y = std::numeric_limits<float>::infinity();
        } else {
            entry.y = invEntry.y / velocity.y;
            exit.y = invExit.y / velocity.y;
        }

        float entryTime = std::max(entry.x, entry.y);
        float exitTime = std::min(exit.x, exit.y);

        if (entryTime > exitTime || entry.x < 0 && entry.y < 0 || entry.x > 1 || entry.y > 1) {
            normal = {0, 0};
            return 1.0f;
        } else {
            if (entry.x > entry.y) {
                if (invEntry.x < 0) {
                    normal = {1, 0};
                } else {
                    normal = {-1, 0};
                }
            } else {
                if (invEntry.y < 0) {
                    normal = {0, 1};
                } else {
                    normal = {0, -1};
                }
            }
            return entryTime;
        }
    }

    // Used along with Swept AABB to get broad phase box of the moving box
    glm::vec4 Collisions::GetSweptBroadPhaseBox(glm::vec4 box, glm::vec2 velocity) {
        glm::vec4 broadPhaseBox;
        broadPhaseBox.x = velocity.x > 0 ? box.x : box.x + velocity.x;
        broadPhaseBox.y = velocity.y > 0 ? box.y : box.y + velocity.y;
        broadPhaseBox.z = velocity.x > 0 ? velocity.x + box.z : box.z - velocity.x;
        broadPhaseBox.w = velocity.y > 0 ? velocity.y + box.w : box.w - velocity.y;

        return broadPhaseBox;
    }
}