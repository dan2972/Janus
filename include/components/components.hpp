#ifndef JANUS_COMPONENTS_HPP
#define JANUS_COMPONENTS_HPP

#include <string>
#include <glm/vec2.hpp>
#include <raylib.h>

namespace Janus {
    enum CollisionResponseType {
        STOP,
        SLIDE
    };

    enum ActorType {
        NONE,
        PLAYER
    };

    struct ActorComponent {
        glm::vec2 position;
        glm::vec2 lastPos;
        glm::vec2 velocity;
        glm::vec2 tilePos;
        glm::vec2 chunkPos;
        glm::vec2 size{32, 32};
        bool collidesWithTiles = true;
        bool collidesWithActors = true;
        ActorType actorType = ActorType::NONE;
        CollisionResponseType collisionResponseType = CollisionResponseType::SLIDE;
    };

    struct RenderComponent {
        Color color;
    };

    struct MovementControllerComponent{
        bool movingRight = false;
        bool movingLeft = false;
        bool movingUp = false;
        bool movingDown = false;
    };

    struct PlayerComponent {
        std::string name;
    };
}

#endif //JANUS_COMPONENTS_HPP
