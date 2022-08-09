#include "random_generator.hpp"

namespace Janus {
    std::default_random_engine RandomGenerator::rng;

    void RandomGenerator::setSeed(int seed) {
        rng.seed(seed);
    }

    int RandomGenerator::randInt(int begin, int end) {
        return (int)rng() % (end - begin + 1) + begin;
    }
}