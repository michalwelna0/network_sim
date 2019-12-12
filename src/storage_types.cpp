#include "../include/storage_types.hpp"



std::string PackageQueue::getFifo_or_Lifo (PackageQueueType type){
    if (type==PackageQueueType ::FIFO){
        return "FIFO";
    }else return "LIFO";

}


const PackageQueueType PackageQueue::get_queue_type() {
    return queue_type;
}

Package PackageQueue :: pop() {

    std::string type = getFifo_or_Lifo(PackageQueueType::FIFO);
    if (type == "FIFO") {

        Package pack = package_queue.front();
        package_queue.pop_front();
        return pack;
    } else {
        Package pack = package_queue.back();
        package_queue.pop_back();
        return pack;
    }

}

const void PackageQueue::push(Package && pack) {
    package_queue.push_back(std::move(pack));
}

const bool PackageQueue::empty() {
    return package_queue.empty();
}

const size_t PackageQueue::size() {
    return package_queue.size();
}