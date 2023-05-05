#pragma once
#include "FastSort.hpp"
#include "HeapSort.hpp"
#include "MergeSort.hpp"
#include "Shell.hpp"
#include "StandartSort.hpp"
#include "Simple.hpp"
#include <variant>

using MasterSorterImplType = std::variant<FastSorter, FastSorterRecurs, HeapSorter,
StandartSorter, ShellSorter, MergeSorterRecursive, MergeSorter, BubbleSorter, SelectionSorter,
InsertSorter>;





class MasterSorter{
private:
    ////
    //отделяем полотно текста
    MasterSorterImplType sorter;
public:
    MasterSorter();
    ~MasterSorter() = default;
    template <class Sorter>
    MasterSorter (Sorter&& sorter) : sorter(std::forward<Sorter>(sorter)){}
    template <class Sorter>
    MasterSorter& operator=(Sorter&& sorter){
        this->sorter = std::forward<Sorter>(sorter);
        return *this;
    }
    template <class It, class Comparator>
    void sort(It begin, It end, Comparator comparator){
        auto visitor = [begin, end, comparator](auto&& sorter){
            sorter.sort(begin, end, comparator);
        };
        auto copy = this->sorter;
        std::visit(visitor, copy);

    }
};