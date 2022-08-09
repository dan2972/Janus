#ifndef JANUS_RANDOM_GENERATOR_HPP
#define JANUS_RANDOM_GENERATOR_HPP

#include <random>

namespace Janus {
    class RandomGenerator {
    public:
        static void setSeed(int seed);
        static int randInt(int begin, int end);
    private:
        static std::default_random_engine rng;
    };
}

#endif //JANUS_RANDOM_GENERATOR_HPP
