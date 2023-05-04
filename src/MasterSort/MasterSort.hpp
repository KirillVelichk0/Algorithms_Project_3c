#pragma once
#include "FastSort.hpp"
#include "HeapSort.hpp"
#include "MergeSort.hpp"
#include "Shell.hpp"
#include "StandartSort.hpp"
#include "Simple.hpp"
#include <variant>

using MasterSorterImplType = std::variant<FastSorter, FastSorterRecurs, HeapSorter, MergeSorter, MergeSorterRecursive,
    ShellSorter, StandartSorter, BubbleSorter, SelectionSorter, InsertSorter>;

//задаем концепты
namespace{
    template <class SomeSorter>
    concept SorterVariantType =
    requires(SomeSorter sorter, MasterSorterImplType impl){
        impl = sorter;
        true;
    };
}



class MasterSorter{
private:
    ////
    //отделяем полотно текста
    MasterSorterImplType sorter;
public:
    MasterSorter();
    ~MasterSorter() = default;
    template <SorterVariantType Sorter>
    MasterSorter (Sorter&& sorter) : sorter(std::forward<Sorter>(sorter)){}
    template <SorterVariantType Sorter>
    MasterSorter& operator=(Sorter&& sorter){
        this->sorter = std::forward<Sorter>(sorter);
        return *this;
    }
    template <class It, class Comparator>
    void sort(It begin, It end, Comparator comparator){
        auto visitor = [&begin, &end, &comparator](auto& sorter){
            sorter.sort(begin, end, comparator);
        };
        std::visit(std::move(visitor), this->sorter);
    }
};