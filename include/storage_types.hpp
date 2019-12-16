#ifndef NETWORK_SIM_STORAGE_TYPES_HPP
#define NETWORK_SIM_STORAGE_TYPES_HPP

#include "types.hpp"
#include "package.hpp"

#include <string>
#include <iostream>
#include <deque>


enum class PackageQueueType { FIFO, LIFO };




class IPackageStockpile{

public:
    virtual void const push(Package&& pack) = 0;
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
    void const push(Package&& pack) override;
    bool const empty() override;
    std::size_t const size() override;
    Package pop() override;
    PackageQueueType const get_queue_type() override;
    std::string getFIFO_or_LIFO(PackageQueueType type);
    using citerator = std::deque<Package>::const_iterator;
    using iterator = std::deque<Package>::iterator;
    citerator cbegin() const {return package_queue.cbegin();}
    citerator cend() const {return package_queue.cend();}
    iterator begin() {return package_queue.begin();}
    iterator end()  {return package_queue.end();}


private:
    PackageQueueType queue_type;
    std::deque<Package> package_queue;

};

#endif //NETWORK_SIM_STORAGE_TYPES_HPP
