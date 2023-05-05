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
    MasterSorter(Sorter&& impl){
        if constexpr (std::is_same_v<MasterSorter, std::decay_t<decltype(impl)>>){
            this->sorter = impl.sorter;
        }
        else{
            this->sorter = impl;
        }
        
    }
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