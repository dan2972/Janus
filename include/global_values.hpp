#ifndef JANUS_GLOBAL_VALUES_HPP
#define JANUS_GLOBAL_VALUES_HPP

namespace Janus {
    static const int TICKS_PER_SECOND = 40;
    static int SCREEN_WIDTH = 800;
    static int SCREEN_HEIGHT = 600;

    static const int CHUNK_TICK_RADIUS = 2;
    static const int CHUNK_LOAD_DISTANCE = 12;
    static const int CHUNK_RENDER_DISTANCE = 5;
    static const int CHUNK_PRELOAD_DISTANCE = 12;

    static const int MAX_CHUNK_TEXTURE_LOAD_PER_RENDER_UPDATE = 4;
}

#endif //JANUS_GLOBAL_VALUES_HPP
