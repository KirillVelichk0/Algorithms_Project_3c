#pragma once
#include <cstdint>
#include <algorithm>
class ShellSorter
{
public:
    template <class It, class Comparator>
    void sort(It begin, It end, Comparator comparator)
    {
        std::int32_t sz = std::distance(begin, end);
        auto SwapCycle = [](auto curIt, auto searcherIt, auto curPos, auto searchPos, auto stepSize)
        {
            while (searchPos < curPos)
            {
                std::swap(*searcherIt, *curIt);
                searchPos += stepSize;
                searcherIt = std::next(searcherIt, stepSize);
            }
        };
        //iterating for lens
        for (std::int32_t curStep = sz / 2; curStep > 0; curStep /= 2)
        {
            auto curGroupBegin = begin;
            //iterating for groups
            for (std::int32_t i = 0; i < curStep; i++, curGroupBegin = std::next(curGroupBegin, 1))
            {
                
                //iterating for group
                for (auto curIt = curGroupBegin, curPos = i; curPos < sz; [&curPos, &curIt, curStep, sz]()
                {
                    curPos+= curStep;
                    if(curPos < sz){
                        curIt = std::next(curIt, curStep);
                    }

                }())
                {
                    auto searcherIt = curGroupBegin;
                    std::int32_t searchPos = i;
                    while (comparator(*searcherIt, *curIt) > 0)
                    {
                        searcherIt = std::next(searcherIt, curStep);
                        searchPos+= curStep;
                    }
                    SwapCycle(curIt, searcherIt, curPos, searchPos, curStep);
                }
            }
        }
    }
};