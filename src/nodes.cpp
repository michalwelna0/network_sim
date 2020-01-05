#include "nodes.hpp"


void ReceiverPreferences::scale_probability() {
    double sum = 0;
    for (const auto& iter: preferences_){
        if (iter.second != 1){
            sum += 1;
        }
        else{
            sum += iter.second;
        }
    }
    for (auto& iter: preferences_){
        iter.second = 1/sum;
    }
}


void ReceiverPreferences::add_receiver(IPackageReceiver *r) {
    preferences_[r] = 1; //narazie niech zerem inicjalizuje, tu ma byc probability_generator()
    scale_probability();
}

void ReceiverPreferences::remove_receiver(IPackageReceiver *r) {
    preferences_.erase(r);
    scale_probability();
}

IPackageReceiver* ReceiverPreferences::choose_receiver() {
    double probability = probability_generator();
    double sum = 0;

    for (const auto& iter : preferences_){
        sum += iter.second;
        if(probability <= sum){
            return iter.first;
        }
    }

    return nullptr;
}

void PackageSender::push_package(Package && pack) {
    PackSenderBufor = std::make_pair(std::move(pack), true);
}

void Worker ::receive_package(Package &&p) {
    q_->push(std::move(p));
}

void Storehouse::receive_package(Package &&p) {
    d_->push(std::move(p));
}

void PackageSender::send_package() {
    if(PackSenderBufor.second){
        receiver_preferences_.choose_receiver()->receive_package(std::move(PackSenderBufor.first));
        PackSenderBufor.second = false;
    }
}

void Ramp::deliver_goods(Time t) {
    if(t % di_== 0){
        Package pack;
        push_package(std::move(pack));
        send_package();
    }
}

//ponizej zmienilem, bo czasem wgl nawet nie wchodzilo do pierwszego ifa i nie przekazywalo nigdzie paczki
// ale nw czy jest dobrze /bw
void Worker::do_work(Time t) {
    bool to_continue = true;
    while ((t - t_) % pd_ == 0) {
        if(!to_continue) {break;}
        if (workerBufor.second) {
            push_package(std::move(workerBufor.first));
            workerBufor.second = false;
            to_continue = false;
        }

        if(q_->size() > 0) {workerBufor = std::make_pair(q_->pop(), true);}
        send_package();
        t_ = t;
    }
}