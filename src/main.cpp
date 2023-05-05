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
#include <cmath>

class HybrydSorter{
private:
    template <class It, class Comparator>
    auto getPartition(It begin, It end, Comparator comparator)
    {
        auto pivot = *begin;
        auto upIt = begin;
        auto downIt = std::next(end, -1);
        while(true){
            while(upIt != end && comparator(*upIt, pivot) == 1){
                upIt++;
            }
            while(comparator(*downIt, pivot) == -1){
                downIt--;
            }
            if(std::distance(upIt, downIt) <= 0){
                return std::next(downIt, 1);
            }
            std::swap(*upIt, *downIt);
            upIt++; downIt--;
        }
    }
    template <class It, class Comparator>
    void rec_sort(It begin, It end, Comparator comparator, std::int16_t curPrice){
        if(curPrice-- == 0){
            HeapSorter sorter;
            sorter.sort(begin, end, comparator);
            return;
        }
        auto size = std::distance(begin, end);
        if (size < 2)
        {
            return;
        }
        auto middlePos = this->getPartition(begin, end, comparator);
        this->rec_sort(begin, middlePos, comparator, curPrice);
        this->rec_sort(middlePos, end, comparator, curPrice);
    }
public:
    template <class It, class Comparator>
    void sort(It begin, It end, Comparator comparator){
        auto size = std::distance(begin, end);
        this->rec_sort(begin, end, comparator, int(std::log2(size)) * 2);
    }
};

int main(int, char**) {
    std::vector<std::string> cont = {"asfdf", "afdsas", "asdf"};
    MasterSorter sorter = BubbleSorter();
    // 3 2 1 
    auto comparator = [](std::string& left, std::string& right) -> std::int32_t{
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
