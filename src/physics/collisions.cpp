#include <algorithm>
#include <cmath>
#include "physics/collisions.hpp"

namespace Janus {
    // Simple AABB collision using two boxes
    bool Collisions::AABB(const glm::vec4& b1, const glm::vec4& b2) {
        return !(b1.x + b1.z < b2.x || b1.x > b2.x + b2.z || b1.y + b1.w < b2.y || b1.y > b2.y + b2.w);
    }

    // Used along with Swept AABB to get broad phase box of the moving box
    glm::vec4 Collisions::GetSweptBroadPhaseBox(const glm::vec4& box, const glm::vec2& velocity) {
        glm::vec4 broadPhaseBox;
        broadPhaseBox.x = velocity.x > 0 ? box.x : box.x + velocity.x;
        broadPhaseBox.y = velocity.y > 0 ? box.y : box.y + velocity.y;
        broadPhaseBox.z = velocity.x > 0 ? velocity.x + box.z : box.z - velocity.x;
        broadPhaseBox.w = velocity.y > 0 ? velocity.y + box.w : box.w - velocity.y;

        return broadPhaseBox;
    }

    // Takes in a ray origin and direction with a target rect to find the collision normal and hit Time [0.0, 1.0]
    bool Collisions::RayVsRect(const glm::vec2 &rayOrigin, const glm::vec2 &rayDir, const glm::vec4 &target,
                               glm::vec2 &normal, float &tHitNear) {
        normal = {0, 0};

        glm::vec2 invDir = 1.0f / rayDir;

        glm::vec2 t_near = (glm::vec2{target.x, target.y} - rayOrigin) * invDir;
        glm::vec2 t_far = (glm::vec2{target.x + target.z, target.y + target.w} - rayOrigin) * invDir;

        if (std::isnan(t_far.y) || std::isnan(t_far.x)) return false;
        if (std::isnan(t_near.y) || std::isnan(t_near.x)) return false;

        if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
        if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

        if (t_near.x > t_far.y || t_near.y > t_far.x) return false;

        tHitNear = std::max(t_near.x, t_near.y);

        float tHitFar = std::min(t_far.x, t_far.y);

        if (tHitFar < 0) return false;

        if (t_near.x > t_near.y) {
            if (invDir.x < 0)
                normal = {1, 0};
            else
                normal = {-1, 0};
        } else {
            if (invDir.y < 0) {
                normal = {0, 1};
                if (t_near.x == t_near.y)
                    normal = {0, 0};
            } else
                normal = {0, -1};
        }
        return true;
    }

    // Checks if a dynamic rectangle collides with a static rectangle using SweptAABB (shooting ray on expanded rect)
    // Returns whether collision happened and the normal and contact time of the collision
    bool Collisions::SweptAABB(const glm::vec4 &rectDynamic, const glm::vec2 &velocity, const glm::vec4 &rectStatic,
                               glm::vec2 &normal, float &contactTime) {
        if (velocity.x == 0 && velocity.y == 0) return false;

        glm::vec4 expandedRect;
        expandedRect.x = rectStatic.x - rectDynamic.z / 2;
        expandedRect.y = rectStatic.y - rectDynamic.w / 2;
        expandedRect.z = rectStatic.z + rectDynamic.z;
        expandedRect.w = rectStatic.w + rectDynamic.w;

        if (RayVsRect({rectDynamic.x + rectDynamic.z / 2, rectDynamic.y + rectDynamic.w / 2},
                      velocity, expandedRect, normal, contactTime)) {
            return (contactTime >= 0.0f && contactTime < 1.0f);
        } else {
            return false;
        }
    }

}