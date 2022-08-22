#ifndef JANUS_ACTOR_RENDER_SYSTEM_HPP
#define JANUS_ACTOR_RENDER_SYSTEM_HPP

#include <raylib.h>
#include "render_system.hpp"
#include "world.hpp"
#include "components/components.hpp"
#include "entities/player_entity.hpp"
#include "glm/common.hpp"
#include "texture_manager.hpp"

namespace Janus {
    class ActorRenderSystem : public RenderSystem{
    public:
        using RenderSystem::RenderSystem;
        void render(float d) override {
            auto view = world->getEntitiesWith<RenderComponent>();
            for (auto entity : view) {
                auto [actor, r] = world->getComponentsFromEntity<ActorComponent, RenderComponent>(entity);

                Texture2D* texture = TextureManager::GetTexture("resources/slime.png");

                glm::vec2 renderPos = glm::mix(actor.lastPos, actor.position, d);
                if (actor.actorType == ActorType::PLAYER)
                    DrawTextureRec(*texture,
                                   {0, 0, static_cast<float>(texture->width), static_cast<float>(texture->height)},
                                   {renderPos.x, renderPos.y}, WHITE);
                else
                    DrawRectanglePro({renderPos.x, renderPos.y, actor.size.x, actor.size.y}, {0, 0}, 0, r.color);
            }
        }
    private:
    };
}

#endif //JANUS_ACTOR_RENDER_SYSTEM_HPP
