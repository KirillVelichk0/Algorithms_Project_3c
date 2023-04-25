#include <iostream>
#include <vector>
#include "Simple/Simple.hpp"
int main(int, char**) {
    std::vector<int> cont = {1, 10, 7, 15, 100, -1};
    MinSorter sorter;
    auto comparator = [](auto left, auto right) -> int{
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
    sorter.sort(cont.begin(), cont.end(), comparator);
    for(auto val: cont){
        std::cout << val << ' ';
    }
}
