#ifndef JANUS_RENDER_SYSTEM_HPP
#define JANUS_RENDER_SYSTEM_HPP

namespace Janus {
    class World;
    class RenderSystem{
    public:
        RenderSystem() = default;
        explicit RenderSystem(World* world) : world{world} {}
        virtual ~RenderSystem() = default;

        virtual void render(float d) = 0;

    protected:
        World* world = nullptr;
    };
}

#endif //JANUS_RENDER_SYSTEM_HPP
