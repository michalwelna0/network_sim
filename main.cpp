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
    PackageQueue q1(PackageQueueType::FIFO);
    PackageQueue q2(PackageQueueType::FIFO);
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(q1);
    std::unique_ptr<IPackageQueue> ptr2 = std::make_unique<PackageQueue>(q2);
    Worker w(1, 2,std::move(ptr1));
    Ramp r(1,2);
    Storehouse s(1, std::move(ptr2));
    r.receiver_preferences_.add_receiver(&w);
    w.receiver_preferences_.add_receiver(&s);
    r.deliver_goods(1);
    r.send_package();
    w.do_work(1);
    w.send_package();
    r.deliver_goods(2);
    r.send_package();
    w.do_work(2);
    w.send_package();
    r.deliver_goods(3);
    r.send_package();
    w.do_work(3);
    w.send_package();
    r.deliver_goods(4);
    r.send_package();
    w.do_work(4);
    w.send_package();

    return 0;

}
