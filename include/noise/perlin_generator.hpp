#ifndef JANUS_PERLIN_GENERATOR_HPP
#define JANUS_PERLIN_GENERATOR_HPP

#include "noise/PerlinNoise.hpp"

namespace Janus {
    class PerlinGenerator {
    public:
        static void initialize(unsigned int seed) {
            noise_seed = seed;
            perlin = siv::PerlinNoise{noise_seed};
        }

        static double getValueAt(float x, float y, float multiplier) {
            return perlin.octave2D_01(x * multiplier, y * multiplier, 4);
        }

    private:
        static siv::PerlinNoise::seed_type noise_seed;
        static siv::PerlinNoise perlin;
    };
}

#endif //JANUS_PERLIN_GENERATOR_HPP
