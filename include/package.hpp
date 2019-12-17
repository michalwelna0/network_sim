#ifndef NETWORK_SIM_PACKAGE_HPP
#define NETWORK_SIM_PACKAGE_HPP
#include "types.hpp"
#include <cstdlib>
#include <set>

class Package{

private:
    ElementID id;
    static std::set<ElementID> assigned_IDs;
    static std::set<ElementID> freed_IDs;
    ElementID assign_id();

public:
    Package() {id = assign_id(); assigned_IDs.emplace(id);};
    Package(const Package&) = default;
    ~Package() {assigned_IDs.erase(id); freed_IDs.emplace(id);};
    Package(Package&& package) : id(std::move(package.id)) {} ;
    ElementID get_id() const {return id;}
    Package& operator=(Package&& package) {freed_IDs.emplace(id); id = std::move(package.id);  return *this;};

};

#endif //NETWORK_SIM_PACKAGE_HPP
