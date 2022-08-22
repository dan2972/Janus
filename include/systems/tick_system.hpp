#ifndef JANUS_TICK_SYSTEM_HPP
#define JANUS_TICK_SYSTEM_HPP

namespace Janus {
    class World;
    class TickSystem{
    public:
        TickSystem() = default;
        explicit TickSystem(World* world) : world{world} {}
        virtual ~TickSystem() = default;

        virtual void tick() = 0;

    protected:
        World* world = nullptr;
    };
}

#endif //JANUS_TICK_SYSTEM_HPP
