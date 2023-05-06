#include "FastSort/FastSort.hpp"
#include "Gen/gen.hpp"
#include "HeapSort/HeapSort.hpp"
#include "Mappers/Mappers.hpp"
#include "MasterSort/MasterSort.hpp"
#include "MergeSort/MergeSort.hpp"
#include "RadixSort/Radix.hpp"
#include "Shell/Shell.hpp"
#include "Simple/Simple.hpp"
#include "StandartSort/StandartSort.hpp"
#include <chrono>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
using nanosec = std::chrono::nanoseconds;
using microsec = std::chrono::microseconds;
using milisec = std::chrono::milliseconds;
struct Comparator {
  std::int32_t operator()(std::string &left, std::string &right) {
    if (right > left) {
      return 1;
    } else if (right < left) {
      return -1;
    } else {
      return 0;
    }
  }

  std::int32_t operator()(digit left, digit right){
    if (right > left) {
      return 1;
    } else if (right < left) {
      return -1;
    } else {
      return 0;
    }
  }
};
template <class Time = nanosec, class Data>
void Compare(std::vector<MasterSorter> &sortings, std::vector<Data> &data,
             const std::string &path) {
  /*Записывает в текстовый файл время сортировки каждой сортировки через
   * пробел*/
  std::ofstream file(path, std::ios::app);
  std::ostream_iterator<std::string> it_file(file, "\n");
  std::string result = "";
  Comparator comparator;
  for (auto it = sortings.begin(); it != sortings.end(); ++it) {
    auto data_copy = data;
    auto start = std::chrono::high_resolution_clock::now();
    it->sort(data_copy.begin(), data_copy.end(), comparator);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<Time>(end - start);
    result += std::to_string(duration.count());
    result += " ";
  }

  *it_file = result;
  it_file++;
  file.close();
}


template <class Data> void Save(std::vector<Data> data, std::string path) {
  /*Сохранение данных в файл*/
  std::ofstream file(path);
  std::ostream_iterator<Data> it_file(file, "\n");
  std::copy(data.begin(), data.end(), it_file);
  file.close();
}
template <class Time>
void CompareRadixDigit(std::vector<std::vector<digit>> data, std::string path) {
  std::ofstream file(path, std::ios::app);
  std::ostream_iterator<std::string> it_file(file, "\n");
  std::string result = "";
  for (auto it = data.begin(); it != data.end(); ++it) {
    auto data_copy = *it;
    RadixSorter sorter;
    auto mapper = GetDigitMapper();
    auto start = std::chrono::high_resolution_clock::now();
    sorter.sort(data_copy.begin(), data_copy.end(), mapper);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<Time>(end - start);
    result += std::to_string(duration.count());
    result += " ";
  }
  *it_file = result;
  it_file++;
  file.close();
}
template <class Time>

void CompareRadixInt(std::vector<std::vector<int>> data, std::string path) {
  std::ofstream file(path, std::ios::app);
  file.seekp(0, std::ios::beg);
  std::ostream_iterator<std::string> it_file(file, "\n");
  std::string result = "";
  for (auto it = data.begin(); it != data.end(); ++it) {
    auto data_copy = *it;
    RadixSorter sorter;
    auto mapper = GetIntMapper();
    auto start = std::chrono::high_resolution_clock::now();
    sorter.sort(data_copy.begin(), data_copy.end(), mapper);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<Time>(end - start);
    result += std::to_string(duration.count());
    result += " ";
  }
  *it_file = result;
  it_file++;
  file.close();
}
template <class Time>

void CompareRadixString(std::vector<std::vector<std::string>> data,
                        std::string path) {
  std::ofstream file(path, std::ios::app);
  std::ostream_iterator<std::string> it_file(file, "\n");
  std::string result = "";
  for (auto it = data.begin(); it != data.end(); ++it) {
    auto data_copy = *it;
    RadixSorter sorter;
    auto mapper = GetStringMapper();
    auto start = std::chrono::high_resolution_clock::now();
    sorter.sort(data_copy.begin(), data_copy.end(), mapper);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<Time>(end - start);
    result += std::to_string(duration.count());
    result += " ";
  }
  *it_file = result;
  it_file++;
  file.close();
}
template <class Time>

void CompareRadixData(std::vector<std::vector<Date>> data, std::string path) {
  std::ofstream file(path, std::ios::app);
  std::ostream_iterator<std::string> it_file(file, "\n");
  std::string result = "";
  for (auto it = data.begin(); it != data.end(); ++it) {
    auto data_copy = *it;
    RadixSorter sorter;
    auto mapper = GetDateMapper();
    auto start = std::chrono::high_resolution_clock::now();
    sorter.sort(data_copy.begin(), data_copy.end(), mapper);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<Time>(end - start);
    result += std::to_string(duration.count());
    result += " ";
  }
  *it_file = result;
  it_file++;
  file.close();
}

template <class Time = nanosec, class Data>
void Compare(MasterSorter sorter, const std::vector<std::vector<Data>> data,
             const std::string &path) {
  /*Записывает в текстовый файл время сортировки каждого вектора данных через
   * пробел*/
  std::ofstream file(path, std::ios::app);
  std::ostream_iterator<std::string> it_file(file, "\n");
  std::string result = "";
  Comparator comparator;
  for (auto it = data.begin(); it != data.end(); ++it) {
    auto data_copy = *it;
    auto start = std::chrono::high_resolution_clock::now();
    sorter.sort(data_copy.begin(), data_copy.end(), comparator);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<Time>(end - start);
    result += std::to_string(duration.count());
    result += " ";
  }

  *it_file = result;
  it_file++;
  file.close();
}



class HybrydSorter {
private:
  template <class It, class Comparator>
  auto getPartition(It begin, It end, Comparator comparator) {
    auto pivot = *begin;
    auto upIt = begin;
    auto downIt = std::next(end, -1);
    while (true) {
      while (upIt != end && comparator(*upIt, pivot) == 1) {
        upIt++;
      }
      while (comparator(*downIt, pivot) == -1) {
        downIt--;
      }
      if (std::distance(upIt, downIt) <= 0) {
        return std::next(downIt, 1);
      }
      std::swap(*upIt, *downIt);
      upIt++;
      downIt--;
    }
  }
  template <class It, class Comparator>
  void rec_sort(It begin, It end, Comparator comparator,
                std::int16_t curPrice) {
    if (curPrice-- == 0) {
      HeapSorter sorter;
      sorter.sort(begin, end, comparator);
      return;
    }
    auto size = std::distance(begin, end);
    if (size < 2) {
      return;
    }
    auto middlePos = this->getPartition(begin, end, comparator);
    this->rec_sort(begin, middlePos, comparator, curPrice);
    this->rec_sort(middlePos, end, comparator, curPrice);
  }

public:
  template <class It, class Comparator>
  void sort(It begin, It end, Comparator comparator) {
    auto size = std::distance(begin, end);
    this->rec_sort(begin, end, comparator, int(std::log2(size)) * 2);
  }
};

auto GetSortersVector(){
  std::vector<MasterSorter> masters;
  masters.push_back(BubbleSorter());
  masters.push_back(InsertSorter());
  masters.push_back(SelectionSorter());
  masters.push_back(ShellSorter());
  masters.push_back(HeapSorter());
  masters.push_back(MergeSorter());
  masters.push_back(MergeSorterRecursive());
  masters.push_back(FastSorter());
  masters.push_back(FastSorterRecurs());
  masters.push_back(StandartSorter());
  return masters;
}
auto GetCoolSorters(){
  std::vector<MasterSorter> masters;
  masters.push_back(HeapSorter());
  masters.push_back(MergeSorter());
  masters.push_back(MergeSorterRecursive());
  masters.push_back(FastSorter());
  masters.push_back(FastSorterRecurs());
  masters.push_back(StandartSorter());
  return masters;
}

auto CompareSmallString(){

  auto data = Gen<std::string, Distribution::PartialMixing>()(5000, 10, 1000, 100, 2000);
  auto masters = GetSortersVector();
  Compare<microsec>(masters, data, "../data/small_str.csv");
}

auto CompareBigString(){
  auto masters = GetCoolSorters();
  auto data = Gen<std::string, Distribution::PartialMixing>()(50000, 20, 10000, 1000, 20000);
  Compare<microsec>(masters, data, "../data/big_str.csv");
}



void GenBubbleDigitData(){
  MasterSorter master{BubbleSorter{}};
  std::vector<std::vector<digit>> data;
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::Uniform>()(50, 10, 100));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::Uniform>()(500, 10, 1000));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(50, 20, 1, 30));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(500, 150, 1, 300));
  }
  Compare<microsec>(master, data, "../data/digit_bubble.csv");
}

void GenInsertDigitData(){
  MasterSorter master = InsertSorter() ;
  std::vector<std::vector<digit>> data;
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::Uniform>()(50, 10, 100));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::Uniform>()(500, 10, 1000));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(50, 20, 1, 30));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(500, 150, 1, 300));
  }
  Compare<microsec>(master, data, "../data/digit_inserter.csv");
}
void GenSelectDigitData(){
  MasterSorter master = SelectionSorter();
  std::vector<std::vector<digit>> data;
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::Uniform>()(50, 10, 100));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::Uniform>()(500, 10, 1000));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(50, 20, 1, 30));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(500, 150, 1, 300));
  }
  Compare<microsec>(master, data, "../data/digit_selection.csv");
}

void GenHeapDigitData(){
  MasterSorter master = HeapSorter();
  MasterSorterImplType impl = HeapSorter();
  std::vector<std::vector<digit>> data;
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::Uniform>()(50, 10, 100));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::Uniform>()(500, 10, 1000));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::Uniform>()(5000, 10, 100));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::Uniform>()(50000, 10, 1000));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(50, 20, 1, 30));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(500, 150, 1, 300));
    
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(50, 20, 1, 30));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(500, 150, 1, 300));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(5000, 2000, 1, 3000));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(50000, 15000, 1, 30000));
  }
  Compare<microsec>(master, data, "../data/digit_heap.csv");
}
void GenMergeDigitData(){
  MasterSorter master = MergeSorter();
  std::vector<std::vector<digit>> data;
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::Uniform>()(50, 10, 100));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::Uniform>()(500, 10, 1000));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::Uniform>()(5000, 10, 100));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::Uniform>()(50000, 10, 1000));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(50, 20, 1, 30));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(500, 150, 1, 300));
    
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(50, 20, 1, 30));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(500, 150, 1, 300));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(5000, 2000, 1, 3000));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(50000, 15000, 1, 30000));
  }
  Compare<microsec>(master, data, "../data/digit_merge.csv");
}
void GenMergeRDigitData(){
  MasterSorter master = MergeSorterRecursive();
  std::vector<std::vector<digit>> data;
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::Uniform>()(50, 10, 100));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::Uniform>()(500, 10, 1000));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::Uniform>()(5000, 10, 100));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::Uniform>()(50000, 10, 1000));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(50, 20, 1, 30));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(500, 150, 1, 300));
    
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(50, 20, 1, 30));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(500, 150, 1, 300));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(5000, 2000, 1, 3000));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(50000, 15000, 1, 30000));
  }
  Compare<microsec>(master, data, "../data/digit_merge_rec.csv");
}

void GenFastRDigitData(){
  MasterSorter master = FastSorterRecurs();
  std::vector<std::vector<digit>> data;
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::Uniform>()(50, 10, 100));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::Uniform>()(500, 10, 1000));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::Uniform>()(5000, 10, 100));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::Uniform>()(50000, 10, 1000));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(50, 20, 1, 30));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(500, 150, 1, 300));
    
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(50, 20, 1, 30));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(500, 150, 1, 300));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(5000, 2000, 1, 3000));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(50000, 15000, 1, 30000));
  }
  Compare<microsec>(master, data, "../data/digit_fast_rec.csv");
}

void GenFastRInt(){
  MasterSorter master = FastSorterRecurs();
  std::vector<std::vector<int>> data;
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<int, Distribution::Normal>()(5000, 100, 1000));
  }

  Compare<microsec>(master, data, "../data/int_fastR_rec.csv");
  data.clear();
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<int, Distribution::Normal>()(50000, 100, 1000));
  }

  Compare<microsec>(master, data, "../data/int_fastR_rec.csv");
  data.clear();
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<int, Distribution::Normal>()(500000, 100, 1000));
  }
  Compare<microsec>(master, data, "../data/int_fastR_rec.csv");
}

void GenFastDigitData(){
  MasterSorter master = FastSorter();
  std::vector<std::vector<digit>> data;
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::Uniform>()(50, 10, 100));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::Uniform>()(500, 10, 1000));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::Uniform>()(5000, 10, 100));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::Uniform>()(50000, 10, 1000));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(50, 20, 1, 30));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(500, 150, 1, 300));
    
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(50, 20, 1, 30));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(500, 150, 1, 300));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(5000, 2000, 1, 3000));
  }
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<digit, Distribution::PartiallyOrdered>()(50000, 15000, 1, 30000));
  }
  Compare<microsec>(master, data, "../data/digit_fast.csv");
}

void GenRadixDate(){
  std::vector<std::vector<Date>> data;
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<Date, Distribution::PartiallyOrdered>()(500000, 30, 100, 30,3, 10));
  }
  CompareRadixData<microsec>(data, "../data/radix_date.csv");
}

void GenRadixInt(){
  std::vector<std::vector<int>> data;
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<int, Distribution::Normal>()(5000, 100, 1000));
  }

  CompareRadixInt<microsec>(data, "../data/radix_int.csv");
  data.clear();
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<int, Distribution::Normal>()(50000, 100, 1000));
  }

  CompareRadixInt<microsec>(data, "../data/radix_int.csv");
  data.clear();
  for(int i = 0; i < 10; i++){
    data.push_back(Gen<int, Distribution::Normal>()(500000, 100, 1000));
  }

  CompareRadixInt<microsec>(data, "../data/radix_int.csv");
}

int main(int, char **) {
  GenMergeDigitData();
  GenMergeRDigitData();
  GenFastDigitData();
  GenFastRDigitData();
  GenHeapDigitData();
  CompareSmallString();
  CompareBigString();
  GenRadixInt();
  GenRadixDate();
  GenFastRInt();
}
