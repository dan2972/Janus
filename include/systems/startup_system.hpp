#ifndef JANUS_STARTUP_SYSTEM_HPP
#define JANUS_STARTUP_SYSTEM_HPP

namespace Janus {
    class World;
    class StartupSystem {
    public:
        StartupSystem() = default;
        explicit StartupSystem(World* world) : world{world} {}
        virtual ~StartupSystem() = default;

        virtual void run() = 0;

    protected:
        World* world = nullptr;
    };
}

#endif //JANUS_STARTUP_SYSTEM_HPP
