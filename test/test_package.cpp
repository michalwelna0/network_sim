#include "gtest/gtest.h"

#include "package.hpp"

TEST(PackageConctructorTest, creatingFirstObject){
    Package pack;
    EXPECT_EQ(1,pack.get_id());
}

TEST(PackageConctructorTest, creatingAnotherObject){
    Package pack1;
    Package pack2;
    Package pack3;
    EXPECT_EQ(1,pack1.get_id());
    EXPECT_EQ(2,pack2.get_id());
    EXPECT_EQ(3,pack3.get_id());
}

TEST(PackageConctructorTest, afterErasingOnePackage){
    Package pack1;
    Package pack2;
    pack2.~Package();
    Package pack3;
    EXPECT_EQ(1,pack1.get_id());
    EXPECT_EQ(2,pack3.get_id());
}

TEST(PackageCopyingConstructorTest, changePackageId){
    Package pack1;
    Package pack2(std::move(pack1));
    Package pack3_1;
    EXPECT_EQ(1, pack2.get_id());
    EXPECT_EQ(2, pack3_1.get_id());
}

TEST(PackageOperatorTest, changingPackageId){
    Package pack1;
    Package pack2;
    pack2 = (std::move(pack1));
    Package pack3_1;
    EXPECT_EQ(1, pack2.get_id());
    EXPECT_EQ(2, pack3_1.get_id());
}