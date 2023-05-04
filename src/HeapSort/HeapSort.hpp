#pragma once
#include <cstdint>
#include <algorithm>
#include <vector>
#include <optional>
#include <type_traits>
template <class T, class Comparator>
class BinareHeap{
private:
    std::vector<T> cont;
    Comparator comparator;
    auto GetParentIndex(std::int32_t curIndex){
        if(curIndex == 0){
            return -1;
        }
        return (curIndex - 1) / 2;
    }
    auto GetLeftChildIndex(std::int32_t curIndex){
        return curIndex * 2 + 1;
    }
    auto GetRightChildIndex(std::int32_t curIndex){
        return curIndex* 2 + 2;
    }
    void Heapify(){
        auto curIndex = 0;
        while(true){
            auto leftIndex = this->GetLeftChildIndex(curIndex);
            auto rightIndex = this->GetRightChildIndex(curIndex);
            auto indexToGo = curIndex;
            if(rightIndex < this->cont.size()){
                if(this->comparator(this->cont[rightIndex], this->cont[leftIndex]) >= 0 
                && this->comparator(this->cont[curIndex], this->cont[leftIndex]) == 1){
                    indexToGo = leftIndex;
                    std::swap(this->cont[curIndex], this->cont[leftIndex]);
                }
                else if(this->comparator(this->cont[rightIndex], this->cont[leftIndex]) == -1 
                && this->comparator(this->cont[curIndex], this->cont[rightIndex]) == 1){
                    indexToGo = rightIndex;
                    std::swap(this->cont[curIndex], this->cont[rightIndex]);
                }
            }
            else if(leftIndex < this->cont.size()){
                if(this->comparator(this->cont[curIndex], this->cont[leftIndex]) == 1){
                    indexToGo = leftIndex;
                    std::swap(this->cont[curIndex], this->cont[leftIndex]);
                }
            }
            if(indexToGo == curIndex){
                break;
            }
            else{
                curIndex = indexToGo;
            }
        }
    }
public:
    BinareHeap(Comparator& comparator) : comparator(comparator) {}
    void Add(const T& val){
        this->cont.push_back(val);
        auto curPos = this->cont.size() - 1;
        auto curParent = this->GetParentIndex(curPos);
        while(curParent>= 0 && comparator(this->cont[curPos], this->cont[curParent]) == -1){
            std::swap(this->cont[curPos], this->cont[curParent]);
            curPos = curParent;
            curParent = this->GetParentIndex(curPos);
        }
    }
    bool IsEmpty() const{
        return this->cont.size() == 0;
    }
    auto TryTop(){
        std::optional<T> result;
        if(this->cont.size() > 0){
            result = this->cont[0];
        }
        return result;
    }
    bool TryPop(){
        bool result = false;
        if(this->cont.size() > 0){
            result = true;
            this->cont[0] = this->cont[this->cont.size() - 1];
            this->cont.pop_back();
            this->Heapify();
        }
        return result;
    }

};


class HeapSorter{
public:
    template <class It, class Comparator>
    void sort(It begin, It end, Comparator comparator){
        using ValType = std::decay_t<decltype(*begin)>;
        auto reverse_comparator = [&comparator](const auto& leftVal, const auto& rightVal){
            return comparator(rightVal, leftVal);
        };
        BinareHeap<ValType, decltype(reverse_comparator)> heap(reverse_comparator);
        std::for_each(begin, end, [&heap](const auto& val){
            heap.Add(val);
        });
        auto curIt = begin;
        while(!heap.IsEmpty()){
            *curIt = heap.TryTop().value();
            heap.TryPop();
            curIt = std::next(curIt, 1);
        }
    }
};