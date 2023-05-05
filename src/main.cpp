#include <iostream>
#include <vector>
#include "RadixSort/Radix.hpp"
#include "Simple/Simple.hpp"
#include "Shell/Shell.hpp"
#include "FastSort/FastSort.hpp"
#include "HeapSort/HeapSort.hpp"
#include "StandartSort/StandartSort.hpp"
#include "MergeSort/MergeSort.hpp"
#include "MasterSort/MasterSort.hpp"
int main(int, char**) {
    std::vector<std::int32_t> cont = {-100, 13, 1, 10000, -23412, 1234, 312, 3123, 13, 1, 1, -322, 228, 15, 2, 3, 10, -19, 22, 1000};
    FastSorter sorter;
    // 3 2 1 
    auto comparator = [](std::int32_t left, std::int32_t right) -> std::int32_t{
        if (right > left){
            return 1;
        }
        else if (right == left){
            return 0;
        }
        else{
            return -1;
        }
    };
    sorter.sort(cont.begin(), cont.end(), comparator);
    for(auto val: cont){
        std::cout << val << ' ';
    }
}
