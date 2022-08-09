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

        enum Type {
            ACTOR,
            PROJECTILE,
            PARTICLE,
            TILE,
            NONE
        };

        [[nodiscard]] glm::vec2 getPos() const { return position; }
        [[nodiscard]] glm::vec2 getSize() const { return size; }
        [[nodiscard]] Type getType() const { return type; }

    protected:
        glm::vec2 position{};
        glm::vec2 size{};

        Type type = Type::NONE;
    };
}

#endif //JANUS_GAME_OBJECT_HPP
