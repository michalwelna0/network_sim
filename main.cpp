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
    /*
    PackageQueue q1(PackageQueueType::FIFO);
    PackageQueue q2(PackageQueueType::FIFO);
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(q1);
    //std::unique_ptr<IPackageStockpile> ptr2 = std::make_unique<PackageQueue>(q2);
    Worker w(1, 2,std::move(ptr1));
    Ramp r(1,2);
    Storehouse s(1, q2);
    r.receiver_preferences_.add_receiver(&w);
    w.receiver_preferences_.add_receiver(&s);

    for(int i=1; i<=6; i++){
        r.deliver_goods(i);
        w.do_work(i);
    }
     */

    PackageQueue q1(PackageQueueType::LIFO);
    PackageQueue q2(PackageQueueType::FIFO);
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(q1);
    std::unique_ptr<IPackageQueue> ptr2 = std::make_unique<PackageQueue>(q2);
    Package p1;
    Package p2;
    Worker w1(1, 1, std::move(ptr1));
    Worker w2(2, 1, std::move(ptr2));
    w1.receive_package(std::move(p1));
    w1.receive_package(std::move(p2));
    w1.receiver_preferences_.add_receiver(&w2);
    w1.do_work(1);
   


    return 0;

}
