#include <iostream>
#include <vector>
#include "RadixSort/Radix.hpp"
#include "Simple/Simple.hpp"
#include "Shell/Shell.hpp"
#include "FastSort/FastSort.hpp"
#include "HeapSort/HeapSort.hpp"
#include "StandartSort/StandartSort.hpp"
#include "MergeSort/MergeSort.hpp"
int main(int, char**) {
    std::vector<std::int32_t> cont = {-11, 1, 10, 7, 15, 100, 10000, -1, 228, 12340};
    RadixSorterRecursive sorter;
    auto comparator = [](auto& left, auto& right) -> int{
        if( right > left){
            return 1;
        }
        else if (right == left){
            return 0;
        }
        else{
            return -1;
        }
    };
    auto mapper = [](std::int32_t val){
        std::uint64_t image;
        if(val < 0){
            val -= INT32_MIN;
            image = val;
        }
        else{
            image = val;
            image -= INT32_MIN;
        }
        
        return image;
    };
    sorter.sort(cont.begin(), cont.end(), mapper);
    /*std::vector<std::uint64_t> cont = {3, 7, 254, 100, 107};
    auto mapper = [](std::uint64_t val){
        return val;
    };
    sorter.sort(cont.begin(), cont.end(), mapper);*/
    for(auto val: cont){
        std::cout << val << ' ';
    }
}
