#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "nodes.hpp"
#include "package.hpp"
#include "storage_types.hpp"
#include "types.hpp"

#include "nodes_mocks.hpp"
#include "global_functions_mock.hpp"

#include <iostream>


TEST(ReceiverPreferencesTest, AddReceiversRescalesProbability) {
    // Upewnij się, że dodanie odbiorcy spowoduje przeskalowanie prawdopodobieństw.
    ReceiverPreferences rp;

    MockReceiver r1;
    rp.add_receiver(&r1);
    ASSERT_NE(rp.get_preferences().find(&r1), rp.get_preferences().end());
    EXPECT_EQ(rp.get_preferences().at(&r1), 1.0);

    MockReceiver r2;
    rp.add_receiver(&r2);
    EXPECT_EQ(rp.get_preferences().at(&r1), 0.5);
    ASSERT_NE(rp.get_preferences().find(&r2), rp.get_preferences().end());
    EXPECT_EQ(rp.get_preferences().at(&r2), 0.5);
}

TEST(ReceiverPreferencesTest, RemoveReceiversRescalesProbability) {
    // Upewnij się, że usunięcie odbiorcy spowoduje przeskalowanie pozostałych prawdopodobieństw.
    ReceiverPreferences rp;

    MockReceiver r1, r2;
    rp.add_receiver(&r1);
    rp.add_receiver(&r2);

    rp.remove_receiver(&r2);
    ASSERT_EQ(rp.get_preferences().find(&r2), rp.get_preferences().end());
    EXPECT_EQ(rp.get_preferences().at(&r1), 1.0);
}

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

    EXPECT_EQ(std::nullopt , r1.get_sending_buffer());
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

    r2.deliver_goods(1);
    r2.send_package();
    r2.deliver_goods(2);

    // jest false, bo czas dostawy jest 1, a worker2 pracuje 2 tury, wiec czeka z wyslaniem
    EXPECT_EQ(std::nullopt,r2.get_sending_buffer());

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

    Ramp r1(1, 1);
    Ramp r2(2, 2);
    Worker w1(1, 1, std::move(ptr1));
    Worker w2(2, 2, std::move(ptr2));

    r2.receiver_preferences_.add_receiver(&w1);

    r2.deliver_goods(1);
    r2.send_package();
    r2.deliver_goods(2);
    r2.send_package();
    r2.deliver_goods(3);
    r2.send_package();

    // jest false bo w deliver_goods wysyla produkt do odbiorcy, zgadza sie argument
    EXPECT_EQ(std::nullopt,r2.get_sending_buffer());

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
    Storehouse s2(2,std::move(ptr4));
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
    w1.send_package();
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
    w1.send_package();
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
    w1.send_package();
    EXPECT_EQ(std::nullopt,w1.get_sending_buffer());
}


TEST(Worker, testing_time_again){
    PackageQueue q1(PackageQueueType::FIFO);
    PackageQueue q2(PackageQueueType::FIFO);
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(q1);
    std::unique_ptr<IPackageStockpile> ptr2 = std::make_unique<PackageQueue>(q2);
    Worker w(1, 2,std::move(ptr1));
    Ramp r(1,2);
    Storehouse s(1, std::move(ptr2));
    r.receiver_preferences_.add_receiver(&w);
    w.receiver_preferences_.add_receiver(&s);
    r.deliver_goods(0);
    r.send_package();
    w.do_work(0);
    w.send_package();
    r.deliver_goods(1);
    r.send_package();
    w.do_work(1);
    w.send_package();
    r.deliver_goods(2);
    r.send_package();
    w.do_work(2);
    w.send_package();


    EXPECT_EQ(1,s.cbegin()->get_id());

}


TEST(WorkerTest, HasBuffer) {
    // Test scenariusza opisanego na stronie:
    // http://home.agh.edu.pl/~mdig/dokuwiki/doku.php?id=teaching:programming:soft-dev:topics:net-simulation:part_nodes#bufor_aktualnie_przetwarzanego_polproduktu

    Worker w(1, 2, std::make_unique<PackageQueue>(PackageQueueType::FIFO));
    Time t = 1;

    // FIXME: poprawić w docelowej wersji (dodać konstruktor z ID półproduktu)
//    w.receive_package(Package(1));
//    w.do_work(t);
//    ++t;
//    w.receive_package(Package(2));
//    w.do_work(t);
//    auto& buffer = w.get_sending_buffer();
    //
    Package p1;
    Package p2;
    w.receive_package(std::move(p1));
    w.do_work(t);
    ++t;
    w.receive_package(std::move(p2));
    w.do_work(t);
    auto& buffer = w.get_sending_buffer();


    ASSERT_TRUE(buffer.has_value());
    EXPECT_EQ(buffer.value().get_id(), 1);
}


TEST(RampTest, IsDeliveryOnTime) {

    Ramp r(1, 2);
    // FIXME: poprawić w docelowej wersji (konstruktor powinien posiadać argument domyślny)
    //auto recv = std::make_unique<Storehouse>(1);
    //auto recv = std::make_unique<Storehouse>(1, std::make_unique<PackageQueue>(PackageQueueType::LIFO));
    PackageQueue q1(PackageQueueType::LIFO);
    std::unique_ptr<IPackageStockpile> ptr = std::make_unique<PackageQueue>(q1);
    Storehouse s(1,std::move(ptr));
    r.receiver_preferences_.add_receiver(&s);

    r.deliver_goods(1);
    ASSERT_TRUE(r.get_sending_buffer().has_value());
    r.send_package();

    r.deliver_goods(2);
    ASSERT_FALSE(r.get_sending_buffer().has_value());

    r.deliver_goods(3);
    ASSERT_TRUE(r.get_sending_buffer().has_value());
}

class PackageSenderFixture : public PackageSender {
    // Nie sposób w teście wykorzystać prywetnej metody `PackageSender::push_package()`,
    // dlatego do celów testowych stworzona została implementacja zawierająca
    // metodę `push_package()` w sekcji publicznej.
public:
    void push_package(Package&& package) { PackageSender::push_package(std::move(package)); }
};

using ::testing::Return;
using ::testing::_;


TEST(PackageSenderTest, SendPackage) {
    MockReceiver mock_receiver;
    // Oczekujemy, że metoda `receive_package()` obiektu `mock_receiver` zostanie
    // wywołana dwukrotnie, z dowolnym argumentem (symbol `_`).
    EXPECT_CALL(mock_receiver, receive_package(_)).Times(1);

    PackageSenderFixture sender;
    sender.receiver_preferences_.add_receiver(&mock_receiver);
    // Zwróć uwagę, że poniższa instrukcja korzysta z semantyki referencji do r-wartości.
    sender.push_package(Package());

    sender.send_package();

    EXPECT_FALSE(sender.get_sending_buffer());

    // Upewnij się, że proces wysyłania zachodzi tylko wówczas, gdy w bufor jest pełny.
    sender.send_package();
}

/*
//FIXME: odkomentować po wyjaśnieniu sytuacji z domyślnym generatorem prawdopodobieństwa
TEST(ReceiverPreferencesChoosingTest, ChooseReceiver) {
    // Upewnij się, że odbiorcy wybierani są z właściwym prawdopodobieństwem.

    GlobalFunctionsMock global_functions_mock;
    EXPECT_CALL(global_functions_mock, generate_canonical()).WillOnce(Return(0.3)).WillOnce(Return(0.7));

    ReceiverPreferences rp;

    MockReceiver r1, r2;
    rp.add_receiver(&r1);
    rp.add_receiver(&r2);

    if (rp.begin()->first == &r1) {
        EXPECT_EQ(rp.choose_receiver(), &r1);
        EXPECT_EQ(rp.choose_receiver(), &r2);
    } else {
        EXPECT_EQ(rp.choose_receiver(), &r2);
        EXPECT_EQ(rp.choose_receiver(), &r1);
    }
}
 */