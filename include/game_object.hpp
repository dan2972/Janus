#ifndef JANUS_GAME_OBJECT_HPP
#define JANUS_GAME_OBJECT_HPP

#include <glm/vec2.hpp>

namespace Janus {
    class GameObject {
    public:
        GameObject() = default;
        virtual ~GameObject() = default;

        virtual void tick() = 0;
        virtual void render(float dt) = 0;

        enum type {
            ACTOR,
            NONE
        };

        glm::vec2 getPos() { return position; }
        glm::vec2 getSize() { return size; }

    protected:
        glm::vec2 position{};
        glm::vec2 size{};
    };
}

#endif //JANUS_GAME_OBJECT_HPP
