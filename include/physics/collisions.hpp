#ifndef JANUS_COLLISIONS_HPP
#define JANUS_COLLISIONS_HPP

#include "glm/vec4.hpp"
#include "glm/vec2.hpp"

namespace Janus {
    class Collisions {
    public:
        static bool AABB(glm::vec4 b1, glm::vec4 b2);
        static float SweptAABB(glm::vec4 box, glm::vec2 velocity, glm::vec4 box2, glm::vec2& normal);
        static glm::vec4 GetSweptBroadPhaseBox(glm::vec4 box, glm::vec2 velocity);
    };
}

#endif //JANUS_COLLISIONS_HPP
