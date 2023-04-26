#include <cstdint>
#include <algorithm>
#include <vector>
#include <type_traits>
class MergeSorterRecursive
{
private:
    template <class It, class RefCont, class Comparator>
    void MergeRefs(It begin, RefCont cont1, RefCont cont2, Comparator comparator)
    {
        auto curIt = begin;
        auto it1 = cont1.cbegin();
        auto it2 = cont2.cbegin();
        while (true)
        {
            if (it1 == cont1.cend())
            {
                while (it2 != cont2.cend())
                {
                    *curIt = (*it2).get();
                    curIt = std::next(curIt, 1);
                    it2 = std::next(it2, 1);
                }
                break;
            }
            else if (it2 == cont2.cend())
            {
                while (it1 != cont1.cend())
                {
                    *curIt = (*it1).get();
                    curIt = std::next(curIt, 1);
                    it1 = std::next(it1, 1);
                }
                break;
            }
            auto compRes = comparator(*it1, *it2);
            if (compRes == 1)
            {
                *curIt = (*it1).get();
                curIt = std::next(curIt, 1);
                it1 = std::next(it1, 1);
            }
            else
            {
                *curIt = (*it2).get();
                curIt = std::next(curIt, 1);
                it2 = std::next(it2, 1);
            }
        }
    }
    template <class It, class RefCont, class Comparator>
    void Merge(It begin, RefCont cont1, RefCont cont2, Comparator comparator)
    {
        auto sz = cont1.size() + cont2.size();
        std::vector<std::decay_t<decltype(cont1.begin()->get())>> result(sz);
        auto curIt = result.begin();
        auto it1 = cont1.cbegin();
        auto it2 = cont2.cbegin();
        while (true)
        {
            if (it1 == cont1.cend())
            {
                while (it2 != cont2.cend())
                {
                    *curIt = (*it2).get();
                    curIt = std::next(curIt, 1);
                    it2 = std::next(it2, 1);
                }
                break;
            }
            else if (it2 == cont2.cend())
            {
                while (it1 != cont1.cend())
                {
                    *curIt = (*it1).get();
                    curIt = std::next(curIt, 1);
                    it1 = std::next(it1, 1);
                }
                break;
            }
            auto compRes = comparator(*it1, *it2);
            if (compRes == 1)
            {
                *curIt = (*it1).get();
                curIt = std::next(curIt, 1);
                it1 = std::next(it1, 1);
            }
            else
            {
                *curIt = (*it2).get();
                curIt = std::next(curIt, 1);
                it2 = std::next(it2, 1);
            }
        }
        auto curItRes = begin;
        for(auto& val: result){
            *curItRes = val;
            curItRes = std::next(curItRes, 1);
        }
    }
    template <class RefIt, class Comparator>
    void RecursiveRefsSort(RefIt begin, RefIt end, Comparator comparator)
    {
        auto sz = std::distance(begin, end);
        if (sz <= 1)
        {
            return;
        }
        else if (sz == 2)
        {
            auto nextIt = std::next(begin, 1);
            if (comparator(*begin, *nextIt) == -1)
            {
                std::swap((*begin).get(), (*nextIt).get());
            }
            return;
        }
        std::vector<std::decay_t<decltype(*begin)>> cont1;
        std::vector<std::decay_t<decltype(*begin)>> cont2;
        auto middleIt = std::next(begin, sz / 2);
        cont1.insert(cont1.cend(), begin, middleIt);
        cont2.insert(cont2.cend(), middleIt, end);
        this->RecursiveRefsSort(cont1.begin(), cont1.end(), comparator);
        this->RecursiveRefsSort(cont2.begin(), cont2.end(), comparator);
        this->MergeRefs(begin, cont1, cont2, comparator);
    }

public:
    // Моя реализация использует выделение памяти со ссылками, 
    // от чего реализация дополняет дополнительную память при финальном слиянии
    // так что при небольших размерах объектов памяти больше,
    // при малых - меньше
    template <class It, class Comparator>
    void sort(It begin, It end, Comparator comparator)
    {
        auto sz = std::distance(begin, end);
        if (sz <= 1)
        {
            return;
        }
        else if (sz == 2)
        {
            auto nextIt = std::next(begin, 1);
            if (comparator(*begin, *nextIt) == -1)
            {
                std::swap(*begin, *nextIt);
            }
            return;
        }
        std::vector<std::reference_wrapper<std::decay_t<decltype(*begin)>>> cont1;
        std::vector<std::reference_wrapper<std::decay_t<decltype(*begin)>>> cont2;
        auto refComparator = [&comparator](auto& left, auto& right)
        {
            return comparator(left.get(), right.get());
        };
        auto middleIt = std::next(begin, sz / 2);
        cont1.insert(cont1.cend(), begin, middleIt);
        cont2.insert(cont2.cend(), middleIt, end);
        this->RecursiveRefsSort(cont1.begin(), cont1.end(), refComparator);
        this->RecursiveRefsSort(cont2.begin(), cont2.end(), refComparator);
        this->Merge(begin, cont1, cont2, comparator);
    }
};