#include "noise/perlin_generator.hpp"

namespace Janus {
    siv::PerlinNoise::seed_type PerlinGenerator::noise_seed;
    siv::PerlinNoise PerlinGenerator::perlin;
}