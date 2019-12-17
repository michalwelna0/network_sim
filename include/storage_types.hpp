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
    virtual bool empty()const = 0;
    virtual std::size_t  size() const = 0;

};

class IPackageQueue:IPackageStockpile{

public:
    virtual Package pop() = 0;
    virtual PackageQueueType  get_queue_type() const = 0;

};

class PackageQueue:IPackageQueue{

public:
    PackageQueue(PackageQueueType queue_type_): queue_type(queue_type_) {}
    void const push(Package&& pack) override;
    bool empty() const  override;
    std::size_t  size()const override;
    Package pop() override;
    PackageQueueType get_queue_type()const override;
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
