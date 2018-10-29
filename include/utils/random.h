#include <chrono>
#include <random>

#ifndef RANDOM_H
#define RANDOM_H

namespace random {
    static unsigned seed
    { static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()) };
    static std::mt19937 engine { random::seed };
};

#endif
