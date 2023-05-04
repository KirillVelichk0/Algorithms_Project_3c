/*Поразрядная сортировка сильно отличается тем,
что для нее не подходит стандартный интерфейс компаратором
Помимо сравнения(или, вместо), поразрядная сортировка должна иметь интерфейс 
преобразования элемента в беззнаковое число*/
//Для лучшего результата, буду работать с байтами, что позволит избежать дорогих операций деления
//Однако, на разных платформах, порядок байт может отличаться. Его надо узнать
#pragma once
#include <algorithm>
#include <cstdint>
#include <vector>
bool IsBigEndian(){
    constexpr std::int32_t a = 0xA1B2C3D4;
    unsigned char *p = (unsigned char*)&a;
    return *p == 0xA1;
}
class RadixSorterRecursive{
private:
    template <class BiecIt, bool isBigEndian, std::int16_t limRadix = 8>
    void rec_sort(BiecIt begin, BiecIt end, std::int16_t curRadix){
        if(curRadix < limRadix){
            std::int16_t curPos;
            if constexpr (isBigEndian){
                curPos = limRadix - 1 - curRadix;
            }
            else{
                curPos = curRadix;
            }
            using InternalType = std::decay_t<decltype(*begin)>;
            std::vector<std::vector<InternalType>> radixes(256);
            auto curIt = begin;
            while(curIt != end){
                auto& val = *curIt;
                unsigned char* bytes_val = (unsigned char*)(&(val.first));
                unsigned char curRadixByte = bytes_val[curPos];
                radixes[curRadixByte].push_back(std::move(val));
                curIt = std::next(curIt, 1);
            }

            std::for_each(radixes.cbegin(), radixes.cend(), [curIt = begin](const auto& oneRadix) mutable{
                std::for_each(oneRadix.cbegin(), oneRadix.cend(), [&curIt](const auto& val){
                    *curIt = std::move(val);
                    curIt = std::next(curIt, 1);
                });
            });
            this->rec_sort<BiecIt, isBigEndian>(begin, end, curRadix + 1);
        }
    }
public:
    //По задумке, Mapper обязан возвращать unsigned int64
    template<class It, class Mapper>
    void sort(It begin, It end, Mapper& mapper){
        using InternalType = std::decay_t<decltype(*begin)>;
        std::vector<std::pair<std::uint64_t, InternalType>> biections;
        {
            auto curIt = begin;
            while(curIt != end){
                auto& val = *curIt;
                biections.push_back(std::make_pair(mapper(val), std::move(val)));
                curIt = std::next(curIt, 1);
            }
        }
        bool isBigEndian = IsBigEndian();
        using ItType = decltype(biections.begin());
        if(isBigEndian){
            this->rec_sort<ItType, true>(biections.begin(), biections.end(), 0);
        }
        else{
            this->rec_sort<ItType, false>(biections.begin(), biections.end(), 0);
        }
        auto curIt = begin;
        for(auto& val: biections){
            *curIt = std::move(val.second);
            curIt = std::next(curIt, 1);
        }
    }
};

class RadixSorter{
public:
    //По задумке, Mapper обязан возвращать unsigned int64
    template<class It, class Mapper>
    void sort(It begin, It end, Mapper& mapper){
        using InternalType = std::decay_t<decltype(*begin)>;
        std::vector<std::pair<std::uint64_t, InternalType>> biections;
        {
            auto curIt = begin;
            while(curIt != end){
                auto& val = *curIt;
                biections.push_back(std::make_pair(mapper(val), std::move(val)));
                curIt = std::next(curIt, 1);
            }
        }
        bool isBigEndian = IsBigEndian();
        using ItType = decltype(biections.begin());
        auto limRadix = 8;
        for(int curRadix = 0; curRadix < limRadix; curRadix++){
            std::int16_t curPos;
            if (isBigEndian){
                curPos = limRadix - 1 - curRadix;
            }
            else{
                curPos = curRadix;
            }
            using InternalType = std::decay_t<decltype(*biections.begin())>;
            std::vector<std::vector<InternalType>> radixes(256);
            auto curIt = biections.begin();
            while(curIt != biections.cend()){
                auto& val = *curIt;
                unsigned char* bytes_val = (unsigned char*)(&(val.first));
                unsigned char curRadixByte = bytes_val[curPos];
                radixes[curRadixByte].push_back(std::move(val));
                curIt = std::next(curIt, 1);
            }

            std::for_each(radixes.cbegin(), radixes.cend(), [curIt = biections.begin()](const auto& oneRadix) mutable{
                std::for_each(oneRadix.cbegin(), oneRadix.cend(), [&curIt](const auto& val){
                    *curIt = std::move(val);
                    curIt = std::next(curIt, 1);
                });
            });
        }
        auto curIt = begin;
        for(auto& val: biections){
            *curIt = std::move(val.second);
            curIt = std::next(curIt, 1);
        }
    }
};
