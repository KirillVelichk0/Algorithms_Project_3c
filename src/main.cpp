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
    std::vector<std::int32_t> cont = {-11, 1, 10, 7, 15, 100, 10000, -1, 228, 12340, -322};
    MasterSorter sorter;
    sorter = StandartSorter();
    sorter = FastSorter();
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
