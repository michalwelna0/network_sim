#include "factory.hpp"

void Factory::remove_ramp(ElementID id) {

    remove_receiver(ramps, id);

}
void Factory::remove_worker(ElementID id){

    auto ptr = find_worker_by_id(id);
    IPackageReceiver *cmp = &(*ptr);
    remove_receiver(workers, id);

    for(auto& elem : workers){

        for(auto& elem_prefs : elem.receiver_preferences_){

            if(elem_prefs.first == cmp){

                elem.receiver_preferences_.remove_receiver(elem_prefs.first);

            }

        }

    }

    for(auto& elem : ramps){

        for(auto& elem_prefs : elem.receiver_preferences_){

            if(elem_prefs.first == cmp){

                elem.receiver_preferences_.remove_receiver(elem_prefs.first);

            }

        }

    }

}

void Factory::remove_storehouse(ElementID id){

    auto ptr = find_worker_by_id(id);
    IPackageReceiver *cmp = &(*ptr);
    remove_receiver(storehouses, id);

    for(auto& elem : workers){

        for(auto& elem_prefs : elem.receiver_preferences_){

            if(elem_prefs.first == cmp){

                elem.receiver_preferences_.remove_receiver(elem_prefs.first);

            }

        }

    }

}