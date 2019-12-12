#ifndef NETWORK_SIM_STORAGE_TYPES_HPP
#define NETWORK_SIM_STORAGE_TYPES_HPP

#include "types.hpp"
#include "package.hpp"

#include <string>
#include <iostream>
#include <deque>


enum class PackageQueueType { FIFO, LIFO };

std::string getFifo_or_Lifo();


class IPackageStockpile{

public:
    virtual void const push(Package&&) = 0;
    virtual bool const empty() = 0;
    virtual std::size_t const size() = 0;

};

class IPackageQueue:IPackageStockpile{

public:
    virtual Package pop() = 0;
    virtual PackageQueueType const  get_queue_type() = 0;

};

class PackageQueue:IPackageQueue{

public:
    PackageQueue(PackageQueueType queue_type_): queue_type(queue_type_) {}
    void const push(Package&&) override;
    bool const empty() override;
    std::size_t const size() override;
    Package pop() override;
    PackageQueueType const get_queue_type() override;

private:
    PackageQueueType queue_type;
    std::deque<Package> package_queue;

};

#endif //NETWORK_SIM_STORAGE_TYPES_HPP
