#ifndef JANUS_COLLISIONS_HPP
#define JANUS_COLLISIONS_HPP

#include "glm/vec4.hpp"
#include "glm/vec2.hpp"

namespace Janus {
    class Collisions {
    public:
        static bool AABB(const glm::vec4& b1, const glm::vec4& b2);
        static glm::vec4 GetSweptBroadPhaseBox(const glm::vec4& box, const glm::vec2& velocity);

        static bool RayVsRect(const glm::vec2& rayOrigin, const glm::vec2& rayDir, const glm::vec4& target, glm::vec2& normal, float& tHitNear);
        static bool SweptAABB(const glm::vec4& rectDynamic, const glm::vec2& velocity, const glm::vec4& rectStatic, glm::vec2& normal, float& contactTime);

    };
}

#endif //JANUS_COLLISIONS_HPP
