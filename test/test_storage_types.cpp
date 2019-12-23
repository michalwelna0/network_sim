#include "gtest/gtest.h"

#include "storage_types.hpp"

TEST(QueueConstructorTest, creatingQueue){
    PackageQueue Fifo_que(PackageQueueType::FIFO);
    PackageQueue Lifo_que(PackageQueueType::LIFO);
    EXPECT_EQ(PackageQueueType::FIFO, Fifo_que.get_queue_type());
    EXPECT_EQ(PackageQueueType::LIFO,Lifo_que.get_queue_type());
}

TEST(QueueEmptyFunctionTest, forEmptyQueue){
    PackageQueue Fifo_que(PackageQueueType::FIFO);
    PackageQueue Lifo_que(PackageQueueType::LIFO);
    EXPECT_TRUE(Fifo_que.empty());
    EXPECT_TRUE(Lifo_que.empty());
}

TEST(QueueEmptyFunctionTest, forNotEmptyQueue){
    PackageQueue Fifo_que(PackageQueueType::FIFO);
    PackageQueue Lifo_que(PackageQueueType::LIFO);
    Package pack1;
    Package pack2;
    Fifo_que.push(static_cast<Package&&>(pack1));
    Lifo_que.push(static_cast<Package&&>(pack2));
    EXPECT_TRUE(!Fifo_que.empty());
    EXPECT_TRUE(!Lifo_que.empty());
}

TEST(QueuePopFunctionTest, takingObjectFromQueue){
    PackageQueue Fifo_que(PackageQueueType::FIFO);
    PackageQueue Lifo_que(PackageQueueType::LIFO);
    Package pack1;
    Package pack2;
    Fifo_que.push(static_cast<Package&&>(pack1));
    Fifo_que.push(static_cast<Package&&>(pack2));
    Lifo_que.push(static_cast<Package&&>(pack1));
    Lifo_que.push(static_cast<Package&&>(pack2));
    EXPECT_EQ(pack1.get_id(),Fifo_que.pop().get_id());
    EXPECT_EQ(pack2.get_id(),Lifo_que.pop().get_id());
}

TEST(QueuePopFunctionTest, erasingObjectFromQueue){
    PackageQueue Fifo_que(PackageQueueType::FIFO);
    PackageQueue Lifo_que(PackageQueueType::LIFO);
    Package pack1;
    Package pack2;
    Fifo_que.push(static_cast<Package&&>(pack1));
    Lifo_que.push(static_cast<Package&&>(pack1));
    Lifo_que.push(static_cast<Package&&>(pack2));
    Fifo_que.pop();
    Lifo_que.pop();
    EXPECT_EQ(0,Fifo_que.size());
    EXPECT_EQ(1,Lifo_que.size());
}

TEST(QueuePushFunctionTest, pushingObjectIntoQueue){
    PackageQueue Fifo_que(PackageQueueType::FIFO);
    PackageQueue Lifo_que(PackageQueueType::LIFO);
    Package pack1;
    Package pack2;
    Fifo_que.push(static_cast<Package&&>(pack1));
    Lifo_que.push(static_cast<Package&&>(pack1));
    Lifo_que.push(static_cast<Package&&>(pack2));
    EXPECT_EQ(Fifo_que.size(),1);
    EXPECT_EQ(Lifo_que.size(),2);
}


