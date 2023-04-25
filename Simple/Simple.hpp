#include <vector>
#include <array>
#include <algorithm>
#include <cstdint>
class BubbleSorter
{
public:
// comparator возвращает 1, если правый элемент больше левого
    template <class It, class Comparator>
    void sort(It begin, It end, Comparator comparator)
    {
        bool smt_checked = false;
        std::int32_t N = std::distance(begin, end);
        for (auto i_it = begin; i_it != end; i_it = std::next(i_it, 1)){
            for (auto j_it = begin; j_it != end; j_it = std::next(j_it, 1)){
                auto next_it = std::next(j_it, 1);
                if(next_it != end && comparator(*j_it, *next_it) == -1){
                    std::swap(*j_it, *next_it);
                    smt_checked = true;
                }
            }
            if(!smt_checked){
                return;
            }
            smt_checked = false;
        }
    }
};

class MinSorter{
    public:
        template <class It, class Comparator>
        void sort(It begin, It end, Comparator comparator){

            for( auto curIt = begin; curIt != end; curIt = std::next(curIt, 1)){
                auto minIt = curIt;
                for(auto searcher_it = curIt; searcher_it != end; searcher_it = std::next(searcher_it, 1)){
                    if(comparator(*minIt, *searcher_it) == -1){
                        minIt = searcher_it;
                    }
                }
                std::swap(*minIt, *curIt);
            }
        }
};


class InsertSorter{
public:
    template <class It, class Comparator>
    void sort(It begin, It end, Comparator comparator){
        std::int32_t curPos = 0;
        auto SwapCycle = [](auto curIt, auto searcherIt, auto curPos, auto searchPos){
            while(searchPos < curPos){
                std::swap(*searcherIt, *curIt);
                searchPos++;
                searcherIt = std::next(searcherIt, 1);
            }
        };
        for(auto curIt = begin; curIt!= end; curIt = std::next(curIt), curPos++){
            auto searcherIt = begin;
            std::int32_t searchPos = 0;
            while(comparator(*searcherIt, *curIt) > 0){
                searcherIt = std::next(searcherIt, 1);
                searchPos++;
            }
            SwapCycle(curIt, searcherIt, curPos, searchPos);
        }

    }
};