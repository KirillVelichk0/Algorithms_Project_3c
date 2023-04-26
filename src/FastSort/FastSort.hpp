#include <cstdint>
#include <algorithm>
#include <random>
class FastSorterRecurs{
    private:
        std::mt19937 randomizer;
    public:
        FastSorterRecurs() : randomizer([](){std::random_device rnd; return rnd();}()) {}
        template<class It, class Comparator>
        void sort(It begin, It end, Comparator comparator){
            if(begin == end || std::next(begin, 1) == end){
                return;
            }
            auto partitioner = [&begin, &end, &comparator, this](){
                std::int32_t sz = std::distance(begin, end);
                std::uniform_int_distribution<std::int32_t> distr(0, sz - 1);
                auto compIndex = distr(this->randomizer);
                auto middlePos = begin;
                auto compVal = *std::next(begin, compIndex);
                std::for_each(begin, end, [compVal, &middlePos, &comparator](auto& curVal){
                    if(comparator(compVal, curVal) == -1){
                        std::swap(*middlePos, curVal);
                        middlePos = std::next(middlePos);
                    }
                
                });
                return middlePos;
            };
            auto middlePos = partitioner();
            this->sort(begin, middlePos, comparator);
            this->sort(middlePos, end, comparator);
            
        }
};