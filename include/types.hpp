#ifndef NETWORK_SIM_TYPES_HPP
#define NETWORK_SIM_TYPES_HPP

#include <functional>

using ElementID = unsigned int;
using Time = int;
using TimeOffset = int;
using ProbabilityGenerator = std::function<double(void)>;
#endif //NETWORK_SIM_TYPES_HPP
