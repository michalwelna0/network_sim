#ifndef NETWORK_SIM_STORAGE_TYPES_HPP
#define NETWORK_SIM_STORAGE_TYPES_HPP

#include "types.hpp"
#include "package.hpp"
#include <string>
#include <iostream>

enum class PackageQueueType { FIFO, LIFO };

std::string getFifo_or_Lifo();


class IPackageStockpile{

public:
    virtual const void push(Package&&) = 0;
    virtual const bool empty() = 0;
    virtual const std::size_t size() = 0;

};

class IPackageQueue{

public:
    virtual Package pop() = 0;
    virtual const PackageQueueType get_queue_type() = 0;

};

class PackageQueue{

public:
    PackageQueueType PackageQueue;

};

#endif //NETWORK_SIM_STORAGE_TYPES_HPP
