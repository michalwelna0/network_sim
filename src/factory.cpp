#include "factory.hpp"

void Factory::remove_ramp(ElementID id) {

    remove_receiver(ramps, id);

}
void Factory::remove_worker(ElementID id){


    auto ptr = find_worker_by_id(id);
    IPackageReceiver *buff = &(*ptr);

    remove_receiver(workers, id);

    for(auto& elem : workers){

        for(auto& elem_prefs : elem.receiver_preferences_){

            if(elem_prefs.first->get_receiver_type() == ReceiverType::WORKER && elem_prefs.first->get_id() == id){

                elem.receiver_preferences_.remove_receiver(elem_prefs.first);

            }

        }

    }

    for(auto& elem : ramps){

        for(auto& elem_prefs : elem.receiver_preferences_){

            if(elem_prefs.first == buff){

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

bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors){

    if(node_colors[sender]==NodeColor::VERIFIED){
        return true;
    }
    node_colors[sender] = NodeColor::VISITED;

    if(sender == nullptr){
        throw NoDefiniedReceivers();
    }

    bool does_sender_have_receiver_diff_than_him = false;
    for(auto& receiver: sender->receiver_preferences_){
        if(receiver.first->get_receiver_type()==ReceiverType::STOREHOUSE){
            does_sender_have_receiver_diff_than_him = true;
        }
        else if(receiver.first->get_receiver_type()==ReceiverType::WORKER){
            //konwersja typów
            IPackageReceiver* receiver_ptr = receiver.first;
            auto worker_ptr = dynamic_cast<Worker*>(receiver_ptr);
            auto sendrecv_ptr = dynamic_cast<PackageSender*>(worker_ptr);

            if(worker_ptr==sender){continue;}
            does_sender_have_receiver_diff_than_him = true;

            if(node_colors[sendrecv_ptr]==NodeColor::UNVISITED){
                has_reachable_storehouse(sendrecv_ptr,node_colors);
            }
        }

    }

    node_colors[sender] = NodeColor::VERIFIED;
    if(has_reachable_storehouse(sender,node_colors)){
        return true;
    }else{throw NoDefiniedReceivers();}

}

bool Factory::is_consistent() const {

    std::map<const PackageSender*, NodeColor> color;
    //obczajcie o chuj chodzi w tym pseudokodzie bo ja nie wiem
    //std::for_each(ramps.cbegin(),ramps.cend(),[color](const auto elem){color[&elem]=NodeColor::UNVISITED;});
    //std::for_each(workers.cbegin(),workers.cend(),[color](const auto elem){color[&elem]=NodeColor::UNVISITED;});

   try {
       for(const auto& ramp: ramps){
           has_reachable_storehouse(&ramp,color);
       }
   } catch(NoDefiniedReceivers&){
       return false;
   }
   return true;

}