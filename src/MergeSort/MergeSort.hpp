#include <cstdint>
#include <algorithm>
#include <vector>
#include <stack>
#include <tuple>
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
        for (auto &val : result)
        {
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
        auto refComparator = [&comparator](auto &left, auto &right)
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

class MergeSorter
{
public:
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
        else
        {
            // If true, than merge

            using Interval = std::tuple<It, It, bool>;
            std::stack<Interval> tasks;
            auto merger = [&comparator](It curB, It curE)
            {
                auto sz = std::distance(curB, curE);
                auto middleIt = std::next(curB, sz / 2);
                std::vector<std::decay_t<decltype(*curB)>> cont;
                auto curIt1 = curB;
                auto curE1 = middleIt;
                auto curIt2 = middleIt;
                auto curE2 = curE;
                while (true)
                {
                    if (curIt1 == curE1)
                    {
                        while (curIt2 != curE2)
                        {
                            cont.push_back(*curIt2);
                            curIt2 = std::next(curIt2);
                        }
                        break;
                    }
                    if (curIt2 == curE2)
                    {
                        while (curIt1 != curE1)
                        {
                            cont.push_back(*curIt1);
                            curIt1 = std::next(curIt1);
                        }
                        break;
                    }
                    if (comparator(*curIt1, *curIt2) == 1)
                    {
                        cont.push_back(*curIt1);
                        curIt1 = std::next(curIt1, 1);
                    }
                    else
                    {
                        cont.push_back(*curIt2);
                        curIt2 = std::next(curIt2, 1);
                    }
                }
                auto curIt = curB;
                for (auto &val : cont)
                {
                    *curIt = val;
                    curIt = std::next(curIt, 1);
                }
            };
            auto sorter = [&comparator, &tasks](It curB, It curE)
            {
                auto sz = std::distance(curB, curE);
                if (sz <= 1)
                {
                    return;
                }
                else if (sz == 2)
                {
                    auto nextIt = std::next(curB, 1);
                    if (comparator(*curB, *nextIt) == -1)
                    {
                        std::swap(*curB, *nextIt);
                    }
                }
                else{
                    auto middleIt = std::next(curB, sz / 2);
                    auto mergeTask = std::make_tuple(curB, curE, true);
                    auto sortTask2 = std::make_tuple(middleIt, curE, false);
                    auto sortTask1 = std::make_tuple(curB, middleIt, false);
                    tasks.push(mergeTask);
                    tasks.push(sortTask2);
                    tasks.push(sortTask1);
                }
            };
            tasks.push(std::make_tuple(begin, end, false));
            while (!tasks.empty())
            {
                auto [curB, curE, isMerge] = tasks.top();
                tasks.pop();
                if (isMerge)
                {
                    merger(curB, curE);
                }
                else
                {
                    sorter(curB, curE);
                }
            }
        }
    }
};