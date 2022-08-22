#include "world.hpp"
#include "entities/entity.hpp"
#include "components/components.hpp"
#include "noise/perlin_generator.hpp"

namespace Janus {
    World::World(GameCamera* camera) : camera{camera} {}

    void World::initialize() {
        PerlinGenerator::initialize(1);

        for (auto& system : startupSystems) {
            system->run();
        }
    }

    void World::tick() {
        for (auto& system : tickSystems) {
            system->tick();
        }
    }

    void World::render(float d) {
        for (auto& system : renderSystems) {
            system->render(d);
        }
    }

    void World::destroyEntity(entt::entity entity) {
        registry.destroy(entity);
    }
}