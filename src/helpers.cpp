#include "helpers.hpp"

std::random_device rd;
std::mt19937 rng(rd());

double probability_generator() {return std::generate_canonical<double, 10>(rng);}