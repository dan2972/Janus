#ifndef JANUS_MOVEMENT_SYSTEM_HPP
#define JANUS_MOVEMENT_SYSTEM_HPP

#include "tick_system.hpp"
#include "components/components.hpp"
#include "world.hpp"

namespace Janus{
    class MovementSystem : public TickSystem {
    public:
        using TickSystem::TickSystem;
        void tick() override {
            auto view = world->getEntitiesWith<MovementControllerComponent>();
            for (auto entity : view) {
                auto& movementController = view.get<MovementControllerComponent>(entity);

                movementController.movingUp = InputManager::MoveUp();
                movementController.movingDown = InputManager::MoveDown();
                movementController.movingLeft = InputManager::MoveLeft();
                movementController.movingRight = InputManager::MoveRight();
            }
        }
    };
}

#endif //JANUS_MOVEMENT_SYSTEM_HPP
