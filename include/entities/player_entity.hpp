#ifndef JANUS_PLAYER_ENTITY_HPP
#define JANUS_PLAYER_ENTITY_HPP

#include "entity.hpp"
#include "components/components.hpp"

namespace Janus {
    struct PlayerEntity : public Entity {
        PlayerEntity(entt::entity entity, World* world, const glm::vec2& pos) : Entity(entity, world) {
            addComponent<ActorComponent>(pos);
            addComponent<RenderComponent>(GREEN);
            addComponent<MovementControllerComponent>();
            addComponent<PlayerComponent>();

            getComponent<ActorComponent>().actorType = ActorType::PLAYER;
        }
    };
}

#endif //JANUS_PLAYER_ENTITY_HPP
