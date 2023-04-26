#include <cstdint>
#include <algorithm>
#include <random>
#include <stack>

class RandomPartitioner{
private:
    std::mt19937 randomizer;
public:
    RandomPartitioner() : randomizer([]() {std::random_device rnd; return rnd(); }()) {}
    template <class It, class Comparator>
    auto getPartition(It begin, It end, Comparator comparator)
    {
        std::int32_t sz = std::distance(begin, end);
        std::uniform_int_distribution<std::int32_t> distr(0, sz - 1);
        auto compIndex = distr(this->randomizer);
        auto middlePos = begin;
        auto compVal = *std::next(begin, compIndex);
        std::for_each(begin, end, [compVal, &middlePos, &comparator](auto &curVal)
                      {
                          if (comparator(compVal, curVal) == -1)
                          {
                              std::swap(*middlePos, curVal);
                              middlePos = std::next(middlePos);
                          }
                      });
        return middlePos;
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
        if (begin == end || std::next(begin, 1) == end)
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
            if (curBegin == curEnd || std::next(curBegin, 1) == curEnd)
            {
                continue;
            }
            auto curMiddle = this->partitioner.getPartition(curBegin, curEnd, comparator);
            tasksCont.push(std::make_pair(curBegin, curMiddle));
            tasksCont.push(std::make_pair(curMiddle, curEnd));
        }
    }
};