#pragma once
#include <cstdint>
#include <algorithm>
#include <random>
#include <stack>

class RandomPartitioner{
public:
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
};
class FastSorterRecurs
{
private:
    RandomPartitioner partitioner;
public:

    template <class It, class Comparator>
    void sort(It begin, It end, Comparator comparator)
    {
        auto size = std::distance(begin, end);
        if (size < 2)
        {
            return;
        }
        auto middlePos = this->partitioner.getPartition(begin, end, comparator);
        this->sort(begin, middlePos, comparator);
        this->sort(middlePos, end, comparator);
    }
};

class FastSorter
{
private:
    RandomPartitioner partitioner;

public:
    template <class It, class Comparator>
    void sort(It begin, It end, Comparator comparator)
    {
        using ItSequence = std::pair<It, It>;
        std::stack<ItSequence> tasksCont;
        tasksCont.push(std::make_pair(begin, end));
        while(!tasksCont.empty()){
            auto [curBegin, curEnd] = tasksCont.top();
            tasksCont.pop();
            auto size = std::distance(curBegin, curEnd);
            if (size < 2)
            {
                continue;
            }
            auto curMiddle = this->partitioner.getPartition(curBegin, curEnd, comparator);
            tasksCont.push(std::make_pair(curBegin, curMiddle));
            tasksCont.push(std::make_pair(curMiddle, curEnd));
        }
    }
};