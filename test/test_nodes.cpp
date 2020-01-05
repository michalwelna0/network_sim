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

TEST(ReceiverPreferences, scaling_probability_while_adding_receivers){
    PackageQueue q1(PackageQueueType::FIFO);
    PackageQueue q2(PackageQueueType::LIFO);
    PackageQueue q3(PackageQueueType::FIFO);
    PackageQueue q4(PackageQueueType::LIFO);
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(q1);
    std::unique_ptr<IPackageQueue> ptr2 = std::make_unique<PackageQueue>(q2);
    std::unique_ptr<IPackageStockpile> ptr3 = std::make_unique<PackageQueue>(q3);
    std::unique_ptr<IPackageStockpile> ptr4 = std::make_unique<PackageQueue>(q4);

    Storehouse s1(1,std::move(ptr3));
    Storehouse s2(2, std::move(ptr4));
    Worker w1(1, 1, std::move(ptr1));
    Worker w2(2, 2, std::move(ptr2));

    ReceiverPreferences rev;
    rev.add_receiver(&s1);
    EXPECT_EQ(rev.cbegin()->second,1);

    rev.add_receiver(&s2);
    std::vector<double> vec;
    for(auto i = rev.cbegin(); i != rev.cend(); i++){
        vec.push_back(i->second);
    }
    EXPECT_EQ(vec[0],0.5);
    EXPECT_EQ(vec[1],0.5);
    vec.clear();

    rev.add_receiver(&w1);
    rev.add_receiver(&w2);

    for(auto i = rev.cbegin(); i != rev.cend(); i++){
        vec.push_back(i->second);
    }
    EXPECT_EQ(vec[0],0.25);
    EXPECT_EQ(vec[1],0.25);
    EXPECT_EQ(vec[2],0.25);
    EXPECT_EQ(vec[3],0.25);
}

TEST(ReceiverPreferences, scaling_probability_while_erasing_receivers){
    PackageQueue q1(PackageQueueType::FIFO);
    PackageQueue q2(PackageQueueType::LIFO);
    PackageQueue q3(PackageQueueType::FIFO);
    PackageQueue q4(PackageQueueType::LIFO);
    PackageQueue q5(PackageQueueType::FIFO);
    PackageQueue q6(PackageQueueType::LIFO);
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(q1);
    std::unique_ptr<IPackageQueue> ptr2 = std::make_unique<PackageQueue>(q2);
    std::unique_ptr<IPackageQueue> ptr6 = std::make_unique<PackageQueue>(q5);
    std::unique_ptr<IPackageStockpile> ptr3 = std::make_unique<PackageQueue>(q3);
    std::unique_ptr<IPackageStockpile> ptr4 = std::make_unique<PackageQueue>(q4);
    std::unique_ptr<IPackageStockpile> ptr5 = std::make_unique<PackageQueue>(q6);

    Storehouse s1(1,std::move(ptr3));
    Storehouse s2(2, std::move(ptr4));
    Storehouse s3(3,std::move(ptr5));
    Worker w1(1, 1, std::move(ptr1));
    Worker w2(2, 2, std::move(ptr2));
    Worker w3(3,3,std::move(ptr6));

    ReceiverPreferences rev;
    rev.add_receiver(&s1);
    rev.add_receiver(&s2);
    rev.add_receiver(&s3);
    rev.add_receiver(&w1);
    rev.add_receiver(&w2);
    rev.add_receiver(&w3);

    rev.remove_receiver(&s1);
    std::vector<double> vec;
    for(auto i = rev.cbegin(); i != rev.cend(); i++){
        vec.push_back(i->second);
    }
    EXPECT_EQ(0.2, vec[0]);
    EXPECT_EQ(0.2, vec[1]);
    EXPECT_EQ(0.2, vec[2]);
    EXPECT_EQ(0.2, vec[3]);
    EXPECT_EQ(0.2, vec[4]);
    vec.clear();

    rev.remove_receiver(&s2);
    for(auto i = rev.cbegin(); i != rev.cend(); i++){
        vec.push_back(i->second);
    }
    EXPECT_EQ(vec[0],0.25);
    EXPECT_EQ(vec[1],0.25);
    EXPECT_EQ(vec[2],0.25);
    EXPECT_EQ(vec[3],0.25);
    vec.clear();

    rev.remove_receiver(&s3);
    rev.remove_receiver(&w1);
    for(auto i = rev.cbegin(); i != rev.cend(); i++){
        vec.push_back(i->second);
    }
    EXPECT_EQ(vec[0],0.5);
    EXPECT_EQ(vec[1],0.5);

}

TEST(ReceiverPreferences, testing_choosing_receiver){
    PackageQueue q1(PackageQueueType::FIFO);
    PackageQueue q2(PackageQueueType::LIFO);
    PackageQueue q3(PackageQueueType::FIFO);
    PackageQueue q4(PackageQueueType::LIFO);
    PackageQueue q5(PackageQueueType::FIFO);
    PackageQueue q6(PackageQueueType::LIFO);
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(q1);
    std::unique_ptr<IPackageQueue> ptr2 = std::make_unique<PackageQueue>(q2);
    std::unique_ptr<IPackageQueue> ptr6 = std::make_unique<PackageQueue>(q5);
    std::unique_ptr<IPackageStockpile> ptr3 = std::make_unique<PackageQueue>(q3);
    std::unique_ptr<IPackageStockpile> ptr4 = std::make_unique<PackageQueue>(q4);
    std::unique_ptr<IPackageStockpile> ptr5 = std::make_unique<PackageQueue>(q6);

    Storehouse s1(1,std::move(ptr3));
    Storehouse s2(2, std::move(ptr4));
    Storehouse s3(3,std::move(ptr5));
    Worker w1(1, 1, std::move(ptr1));
    Worker w2(2, 2, std::move(ptr2));
    Worker w3(3,3,std::move(ptr6));

    ReceiverPreferences rev;
    rev.add_receiver(&s1);
    rev.add_receiver(&s2);
    rev.add_receiver(&s3);
    rev.add_receiver(&w1);
    rev.add_receiver(&w2);

    IPackageReceiver* rec = rev.choose_receiver();
    EXPECT_EQ(rec , &w2);
}

TEST(Storehouse, testing_receiving_package){

    PackageQueue q1(PackageQueueType::FIFO);
    PackageQueue q2(PackageQueueType::LIFO);
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(q1);
    std::unique_ptr<IPackageQueue> ptr2 = std::make_unique<PackageQueue>(q2);
    Package p1;
    Package p2;
    Storehouse s1(1, std::move(ptr1));
    Storehouse s2(2, std::move(ptr2));
    s1.receive_package(std::move(p1));
    s2.receive_package(std::move(p2));
    EXPECT_EQ(s1.cend()->get_id(), p1.get_id());
    EXPECT_EQ(s2.cbegin()->get_id(), p2.get_id());

}

TEST(Worker, testing_receiving_package){

    PackageQueue q1(PackageQueueType::FIFO);
    PackageQueue q2(PackageQueueType::LIFO);
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(q1);
    std::unique_ptr<IPackageQueue> ptr2 = std::make_unique<PackageQueue>(q2);
    Package p1;
    Package p2;
    Worker w1(1, 1, std::move(ptr1));
    Worker w2(2, 1, std::move(ptr2));
    w1.receive_package(std::move(p1));
    w2.receive_package(std::move(p2));
    EXPECT_EQ(w1.cend()->get_id(), p1.get_id());
    EXPECT_EQ(w2.cbegin()->get_id(), p2.get_id());

}

TEST(Worker, testing_sent_package_FIFO){

    PackageQueue q1(PackageQueueType::FIFO);
    PackageQueue q2(PackageQueueType::LIFO);
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
    EXPECT_EQ(w2.cbegin()->get_id(), 1);

}

TEST(Worker, testing_sent_package_LIFO){

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
    EXPECT_EQ(w2.cbegin()->get_id(), 2);

}
//ponizszy test nie testuje tego co powinien, nie wiem jak tu dziala czas XD /bw
 TEST(Worker, testing_working_time){

    PackageQueue q1(PackageQueueType::FIFO);
    PackageQueue q2(PackageQueueType::LIFO);
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(q1);
    std::unique_ptr<IPackageQueue> ptr2 = std::make_unique<PackageQueue>(q2);
    Package p1;
    Package p2;
    Worker w1(1, 1, std::move(ptr1));
    Worker w2(2, 2, std::move(ptr2));
    w1.receive_package(std::move(p1));
    w2.receive_package(std::move(p2));
    w1.receiver_preferences_.add_receiver(&w2);
    w1.do_work(1);
    EXPECT_FALSE(w1.get_buffer().second);
}
