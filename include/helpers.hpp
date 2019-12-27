#ifndef NETWORK_SIM_HELPERS_HPP
#define NETWORK_SIM_HELPERS_HPP
#include "types.hpp"
#include <random>
#include <ctime>
#include <cstdlib>

std::random_device rd;
std::mt19937 rng(rd());

ProbabilityGenerator probability_generator() {
    return std::generate_canonical<double, 10>(rng);
}

#endif //NETWORK_SIM_HELPERS_HPP
