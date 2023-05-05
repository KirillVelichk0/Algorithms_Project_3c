#pragma once
#include <algorithm>
class StandartSorter{
public:
    template <class It, class Comparator>
    void sort(It begin, It end, Comparator comparator){
        auto comparatorForStdSort = [comparator](auto& lhs, auto& rhs){
            return comparator(lhs, rhs) == 1;
        };
        std::sort(begin, end, comparatorForStdSort);
    }
};