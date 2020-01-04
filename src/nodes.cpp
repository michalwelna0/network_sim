#include "nodes.hpp"


void ReceiverPreferences::scale_probability() {
    double sum = 0;

    for (const auto& iter : preferences_){
        sum += iter.second;
    }

    for (auto& iter: preferences_){
        iter.second /= sum;
    }
}


void ReceiverPreferences::add_receiver(IPackageReceiver *r) {
    preferences_[r] = 0.4; //narazie niech zerem inicjalizuje, tu ma byc probability_generator()
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

void Worker::do_work(Time t) {
    if ((t - t_) % pd_ == 0) {
        if (workerBufor.second) {
            push_package(std::move(workerBufor.first));
            workerBufor.second = false;
        }

        workerBufor = std::make_pair(q_->pop(), true);
        send_package();
        t_ = t;
    }
}