#include "factory.hpp"

void Factory::remove_ramp(ElementID id) {

    remove_receiver(ramps, id);

}
void Factory::remove_worker(ElementID id){

    remove_receiver(workers, id);

    for(auto& elem : workers){

        for(auto& elem_prefs : elem.receiver_preferences_){

            if(elem_prefs.first->get_receiver_type() == ReceiverType::WORKER && elem_prefs.first->get_id() == id){

                elem.receiver_preferences_.remove_receiver(elem_prefs.first);

            }

        }

    }
//michal welna
    for(auto& elem : ramps){

        for(auto& elem_prefs : elem.receiver_preferences_){

            if(elem_prefs.first->get_receiver_type() == ReceiverType::WORKER && elem_prefs.first->get_id() == id){

                elem.receiver_preferences_.remove_receiver(elem_prefs.first);

            }

        }

    }

}

void Factory::remove_storehouse(ElementID id){

    remove_receiver(storehouses, id);

    for(auto& elem : workers){

        for(auto& elem_prefs : elem.receiver_preferences_){

            if(elem_prefs.first->get_receiver_type() == ReceiverType::STOREHOUSE && elem_prefs.first->get_id() == id){

                elem.receiver_preferences_.remove_receiver(elem_prefs.first);

            }

        }

    }

}