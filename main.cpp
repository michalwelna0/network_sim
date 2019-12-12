#include <iostream>
#include "include/package.hpp"
#include "include/storage_types.hpp"
#include "include/types.hpp"
int main(){

    Package test_pack = Package();
    ElementID id = test_pack.get_id();
    //std::cout << id <<std::endl;
    Package test_pack2 = Package();
    ElementID id2 = test_pack2.get_id();
    //std::cout << id2;
    Package test_pack3 = Package();
    ElementID id3 = test_pack3.get_id();
    //std::cout << id3;
    return 0;

}
