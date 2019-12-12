#ifndef NETWORK_SIM_PACKAGE_HPP
#define NETWORK_SIM_PACKAGE_HPP
#include "types.hpp"
#include <cstdlib>
#include <set>

static std::set<ElementID> assigned_IDs;
static std::set<ElementID> freed_IDs;

class Package{

private:
    ElementID id;

public:
    Package() {};
    Package(const Package&) = default;
    Package(const Package&&);
    const ElementID get_id() {return id;}
    Package& operator=(Package&& other) {
        id = std::move(other.get_id());
        return *this;
    };

};

#endif //NETWORK_SIM_PACKAGE_HPP
