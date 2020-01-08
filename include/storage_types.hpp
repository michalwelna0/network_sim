#ifndef NETWORK_SIM_STORAGE_TYPES_HPP
#define NETWORK_SIM_STORAGE_TYPES_HPP

#include "types.hpp"
#include "package.hpp"

#include <string>
#include <iostream>
#include <deque>
#include <list>


enum class PackageQueueType { FIFO, LIFO };




class IPackageStockpile{

public:
    virtual void push(Package&& pack) = 0;
    virtual bool empty()const = 0;
    virtual std::size_t  size() const = 0;
    using const_iterator = std::list<Package>::const_iterator;
    virtual const_iterator cbegin () const = 0;
    virtual const_iterator cend() const = 0;
    virtual const_iterator begin() const = 0;
    virtual const_iterator end () const = 0;
    virtual ~IPackageStockpile() {};
};

class IPackageQueue: public IPackageStockpile{

public:
    virtual Package pop() = 0;
    virtual PackageQueueType  get_queue_type() const = 0;

};

class PackageQueue: public IPackageQueue{

public:
    PackageQueue(PackageQueueType queue_type_): queue_type(queue_type_) {}
    void push(Package&& pack) override;
    bool empty() const  override;
    std::size_t  size()const override;
    Package pop() override;
    PackageQueueType get_queue_type()const override;
    std::string getFIFO_or_LIFO(PackageQueueType type);
    const_iterator cbegin() const override {return package_queue.cbegin();}
    const_iterator cend() const override  {return package_queue.cend();}
    const_iterator begin() const override {return package_queue.begin();}
    const_iterator end() const override {return package_queue.end();}



private:
    PackageQueueType queue_type;
    std::list<Package> package_queue;

};

#endif //NETWORK_SIM_STORAGE_TYPES_HPP
