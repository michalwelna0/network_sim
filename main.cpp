#include <iostream>
#include <vector>
#include "include/package.hpp"
#include "include/storage_types.hpp"
#include "include/types.hpp"
int main(){

    Package test = Package(); std::cout << test.get_id() << " ";
    Package test1 = Package();std::cout << test1.get_id() << " ";
    Package test2 = Package();std::cout << test2.get_id() << " ";
    Package test3 = Package();std::cout << test3.get_id() << " ";
    Package test4 = Package();std::cout << test4.get_id() << " ";
    PackageQueue test_FIFO_queue = PackageQueue(PackageQueueType::LIFO);
    test_FIFO_queue.push(static_cast<Package &&>(test)); test_FIFO_queue.push(static_cast<Package &&>(test1));
    test_FIFO_queue.push(static_cast<Package &&>(test2));test_FIFO_queue.push(static_cast<Package &&>(test3));
    test_FIFO_queue.push(static_cast<Package &&>(test4));
    Package pack = test_FIFO_queue.pop();
    std::cout<<pack.get_id();

}
