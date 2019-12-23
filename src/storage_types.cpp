#include "storage_types.hpp"



std::string PackageQueue::getFIFO_or_LIFO (PackageQueueType type){

    if (type==PackageQueueType ::FIFO){
        return "FIFO";
    }else return "LIFO";

}


PackageQueueType PackageQueue::get_queue_type() const {
   return queue_type;
}

Package PackageQueue :: pop() {

    std::string type = getFIFO_or_LIFO(get_queue_type());
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

void PackageQueue::push(Package && pack) {
    package_queue.push_back(std::move(pack));
}

bool PackageQueue::empty() const {
    return package_queue.empty();
}

 size_t PackageQueue::size() const {
    return package_queue.size();
}
