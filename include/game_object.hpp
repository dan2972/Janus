#ifndef JANUS_GAME_OBJECT_HPP
#define JANUS_GAME_OBJECT_HPP

#include <glm/glm.hpp>

namespace Janus {
    class GameObject {
    public:
        GameObject() = default;
        virtual ~GameObject() = default;

        virtual void update(float deltaTime) = 0;
        virtual void render() = 0;

        enum type {
            ACTOR,
            NONE
        };
    protected:
        glm::vec2 position{};
    };
}

#endif //JANUS_GAME_OBJECT_HPP
