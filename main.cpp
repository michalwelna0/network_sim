#include <iostream>
#include "package.hpp"
#include "storage_types.hpp"
#include "types.hpp"
#include "factory.hpp"
#include "helpers.hpp"
#include "nodes.hpp"
#include "reports.hpp"
#include "simulation.hpp"

int main(){

    Factory factory;
    factory.add_ramp(Ramp(1, 1));
    factory.add_worker(Worker(1, 1, std::make_unique<PackageQueue>(PackageQueueType::FIFO)));

    Ramp& r = *(factory.find_ramp_by_id(1));
    Worker& w = *(factory.find_worker_by_id(1));
    r.receiver_preferences_.add_receiver(&w);

    factory.remove_worker(w.get_id());

    auto prefs = r.receiver_preferences_.get_preferences();


}
