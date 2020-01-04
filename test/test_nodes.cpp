#include "gtest/gtest.h"

#include "nodes.hpp"

TEST(PackageSenderTEST, isBuforEmptyAfterSending){
    //czy po wyslaniu polproduktu, bufor jest pusty?

    PackageQueue q1(PackageQueueType::FIFO);
    PackageQueue q2(PackageQueueType::LIFO);
    PackageQueue q3(PackageQueueType::FIFO);
    PackageQueue q4(PackageQueueType::LIFO);
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(q1);
    std::unique_ptr<IPackageQueue> ptr2 = std::make_unique<PackageQueue>(q2);
    std::unique_ptr<IPackageStockpile> ptr3 = std::make_unique<PackageQueue>(q3);
    std::unique_ptr<IPackageStockpile> ptr4 = std::make_unique<PackageQueue>(q4);
    Storehouse s1(1, std::move(ptr3));
    Storehouse s2(2, std::move(ptr4));
    Ramp r1(1, 1);
    Ramp r2(2, 2);
    Worker w1(1, 1, std::move(ptr1));
    Worker w2(2, 2, std::move(ptr2));

    r1.receiver_preferences_.add_receiver(&w1);


    r1.deliver_goods(0);
    r1.send_package();

    EXPECT_EQ(false , r1.get_sending_buffer().second);
}

//pisac testy, funkcja choose_receiver jest do poprawy, ogolnie tam dystrybuante trzeba lepiej zrobic, ale to inne testy trzeba napisac


TEST(RampTest, isBuforNotEmptyDoesItFullCorrectly){
    //czy dobrze idzie do bufora na dostawie?

    PackageQueue q1(PackageQueueType::FIFO);
    PackageQueue q2(PackageQueueType::LIFO);
    PackageQueue q3(PackageQueueType::FIFO);
    PackageQueue q4(PackageQueueType::LIFO);
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(q1);
    std::unique_ptr<IPackageQueue> ptr2 = std::make_unique<PackageQueue>(q2);
    std::unique_ptr<IPackageStockpile> ptr3 = std::make_unique<PackageQueue>(q3);
    std::unique_ptr<IPackageStockpile> ptr4 = std::make_unique<PackageQueue>(q4);
    Storehouse s1(1, std::move(ptr3));
    Storehouse s2(2, std::move(ptr4));
    Ramp r1(1, 1);
    Ramp r2(2, 2);
    Worker w1(1, 1, std::move(ptr1));
    Worker w2(2, 2, std::move(ptr2));

    r2.receiver_preferences_.add_receiver(&w1);

    r2.deliver_goods(0);
    r2.send_package();
    r2.deliver_goods(1);

    // jest false, bo czas dostawy jest 1, a worker2 pracuje 2 tury, wiec czeka z wyslaniem
    EXPECT_EQ(false,r2.get_sending_buffer().second);

}

TEST(RampTest1, isBuforNotEmptyDoesItFullCorrectly){
    //czy dobrze idzie do bufora na dostawie?

    PackageQueue q1(PackageQueueType::FIFO);
    PackageQueue q2(PackageQueueType::LIFO);
    PackageQueue q3(PackageQueueType::FIFO);
    PackageQueue q4(PackageQueueType::LIFO);
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(q1);
    std::unique_ptr<IPackageQueue> ptr2 = std::make_unique<PackageQueue>(q2);
    std::unique_ptr<IPackageStockpile> ptr3 = std::make_unique<PackageQueue>(q3);
    std::unique_ptr<IPackageStockpile> ptr4 = std::make_unique<PackageQueue>(q4);
    Storehouse s1(1, std::move(ptr3));
    Storehouse s2(2, std::move(ptr4));
    Ramp r1(1, 1);
    Ramp r2(2, 2);
    Worker w1(1, 1, std::move(ptr1));
    Worker w2(2, 2, std::move(ptr2));

    r2.receiver_preferences_.add_receiver(&w1);

    r2.deliver_goods(0);
    r2.send_package();
    r2.deliver_goods(1);
    r2.send_package();
    r2.deliver_goods(2);

    // jest false bo w deliver_goods wysyla produkt do odbiorcy, zgadza sie argument
    EXPECT_EQ(false,r2.get_sending_buffer().second);

}