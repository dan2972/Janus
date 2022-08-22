#ifndef JANUS_TILE_DATA_HPP
#define JANUS_TILE_DATA_HPP

namespace Janus {
    static const int TILE_SIZE = 32;

    enum class GroundTileID {
        NONE,
        GRASS,
        STONE,
        WATER,
        SAND
    };

    enum class ObjectTileID {
        NONE,
        AIR,
        STONE
    };

    struct GroundTile {
        GroundTileID id = GroundTileID::NONE;
    };

    struct ObjectTile{
        ObjectTileID id = ObjectTileID::NONE;
        int tileX{};
        int tileY{};
        bool collidable = false;
        bool mouseOver = false;
        short health{};
    };
}

#endif //JANUS_TILE_DATA_HPP
