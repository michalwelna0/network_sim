#include "../include/storage_types.hpp"



std::string getFifo_or_Lifo(PackageQueueType &type){
    if (type==PackageQueueType ::FIFO){
        return "FIFO";
    }else return "LIFO";

}


