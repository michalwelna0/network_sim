#include <iostream>
#include "package.hpp"

std::set<ElementID> Package::assigned_IDs={};
std::set<ElementID> Package::freed_IDs={};

ElementID Package::assign_id() {

    ElementID id_to_assign = 0;

    if(freed_IDs.empty()){
        if(assigned_IDs.empty()){

            id_to_assign = 1;

        }
        else{

            id_to_assign = *(assigned_IDs.rbegin()) + 1;

        }

    }
    else{

        id_to_assign = *(freed_IDs.begin());
        freed_IDs.erase(id_to_assign);

    }
    return id_to_assign;

}