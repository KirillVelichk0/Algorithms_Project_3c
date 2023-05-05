#pragma once
#include <chrono>
#include <random>
#include <string>
#include <type_traits>
#include <vector>
#include <algorithm>
#include <iostream>
using digit = char; //одноразрядное число :-)
class Date { // struct for example
public:
  Date(int year = 0, int month = 0, int day = 0) : year_(year), month_(month), day_(day) {}

  int year() const { return year_; }
  int month() const { return month_; }
  int day() const { return day_; }

  std::string toString() {
    return std::to_string(year_) + "." + std::to_string(month_) + "." + std::to_string(day_);
  }
  bool operator==(Date d) { // for comparator
    return year_ == d.year_ && month_ == d.month_ && day_ == d.day_;
  }
  bool operator>(Date d) { // frr comparator
    if (year_ > d.year_)
      return true;
    else if (year_ == d.year_) {
      if (month_ > d.month_)
        return true;
      else if (month_ == d.month_) {
        return day_ > d.day_;
      }
    }
    return false;
  }
  bool operator<(Date d) { //long time operator
    return !operator==(d) && !operator>(d);
  }

private:
  int year_;
  int month_;
  int day_;
};

//enum class TypeForGen { Digit, Number, String, DataStruct }; // Digit is char!
enum class Distribution { Uniform, PartiallyOrdered, PartialMixing, Normal };

inline auto CreateGenerator() {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  return std::default_random_engine(seed);
}













/////генераторы данных/////
template <class type,
          Distribution dist = Distribution::Uniform>
auto Gen() {
  return 0;
}

template <>
inline auto
Gen<digit,
    Distribution::Uniform>() { //равномерное распределение для одного разряда, с
                               //указанием границ (0-9)
  return [](size_t size, int a = 0, int b = 9) {
    auto generator = CreateGenerator();
    std::vector<char> v(size);
    std::uniform_int_distribution<int> distribution(a, b);
    for (auto it = v.begin(); it != v.end(); ++it)
      *it = '0' + distribution(generator);
    return v;
  };
}
template <>
inline auto
Gen<double,
    Distribution::Uniform>() { //нормальное распределение для чисел (double) c
                               //указанием среднего и дисперсии (по умолчанию -
                               //стандартное)
  return [](size_t size, double a = 0, double b = 1) {
    auto generator = CreateGenerator();
    std::vector<double> v(size);
    std::uniform_real_distribution<double> distribution(a, b);
    for (auto it = v.begin(); it != v.end(); ++it)
      *it = distribution(generator);
    return v;
  };
}
template <>
inline auto
Gen<int,
    Distribution::Uniform>() { //нормальное распределение для чисел (double) c
                               //указанием среднего и дисперсии (по умолчанию -
                               //стандартное)
  return [](size_t size, int a = 0, int b = 1) {
    auto generator = CreateGenerator();
    std::vector<int> v(size);
    std::uniform_int_distribution<int> distribution(a, b);
    for (auto it = v.begin(); it != v.end(); ++it)
      *it = distribution(generator);
    return v;
  };
}
template <> inline auto Gen<std::string, Distribution::Uniform>() {
  return [](size_t size, int max_len) {
    auto generator = CreateGenerator();
    std::vector<std::string> v(size);
    std::uniform_int_distribution<char> distribution('a', 'z');
    for (auto it = v.begin(); it != v.end(); ++it) {
      int len = std::uniform_int_distribution<int>(1, max_len)(generator);
      for (int i = 0; i < len; ++i) {
        (*it).push_back(distribution(generator));
      }
    }
    return v;
  };
}

template <>
inline auto Gen<Date,
    Distribution::Uniform>() { //равномерное распределение для одного разряда, с
                               //указанием границ (0-9)
  return [](size_t size, int min_year, int max_year) {
    auto generator = CreateGenerator();
    std::vector<Date> v(size);
    std::uniform_int_distribution<int> year_dis(min_year, max_year);
    std::uniform_int_distribution<int> month_dis(1, 12);
    for (auto it = v.begin(); it != v.end(); it = std::next(it, 1)) {
      int year = year_dis(generator);
      int month = month_dis(generator);
      int day = 1;

      // Определяем количество дней в месяце
      if (month == 2) {
        if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
          day = 29;
        } else {
          day = 28;
        }
      } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        day = 30;
      } else {
        day = 31;
      }

      std::uniform_int_distribution<int> day_dis(1, day);
      day = day_dis(generator);

      *it = Date(year, month, day);
    }
    return v;
  };
}

template <> inline auto Gen<double, Distribution::Normal>() {
  return [](size_t size, double mean = 0, double var = 1) {
    auto generator = CreateGenerator();
    std::vector<double> v(size);
    std::normal_distribution<double> distribution(mean, var);
    for (auto it = v.begin(); it != v.end(); ++it)
      *it = distribution(generator);
    return v;
  };
}
template <> inline auto Gen<int, Distribution::Normal>() {
  return [](size_t size, double mean = 0, double var = 1) {
    auto generator = CreateGenerator();
    std::vector<int> v(size);
    std::normal_distribution<double> distribution(mean, var);
    for (auto it = v.begin(); it != v.end(); ++it)
      *it = (int) distribution(generator);
    return v;
  };
}
template <> inline auto Gen<digit, Distribution::PartiallyOrdered>() {
  return [](size_t size, int count, int a, int b) {
    if(!(a <= b && b <= size)) throw;
    auto generator = CreateGenerator();
    std::vector<char> v(size);
    std::uniform_int_distribution<char> distribution_for_count(0, size);
    int index_digit[10];
    for(int i = 0; i < 10; ++i) {
      index_digit[i] = distribution_for_count(generator);
    }
    
    std::sort(index_digit, index_digit+10);
    int count_digit[10];
    count_digit[0] = index_digit[0];
    int sum = count_digit[0];
    for(int i = 1; i < 9; ++i) {
      count_digit[i] = index_digit[i] - index_digit[i-1];
      sum += count_digit[i];
    }
    count_digit[9] = size - sum;
    int i = 0;
    auto it = v.begin();
    while(it != v.end() && i != 10) {
      if(count_digit[i] != 0) {
        *it = i + '0';
        it++;
        count_digit[i]--;
      } else i++;
    }
    std::uniform_int_distribution<int> distribution(a, b);
    std::uniform_int_distribution<int> distribution_for_digit('0', '9');
    while(count-- != 0) {
      v[distribution(generator)] = distribution_for_digit(generator);
    }
    

    return v;
  };
}

template <> inline auto Gen<double, Distribution::PartiallyOrdered>() {
  return [](size_t size, double a, double b, int count, int i, int j) {
    if(!(i <= j && j <= size)) throw;
    auto generator = CreateGenerator();
    std::vector<double> v = Gen<double, Distribution::Uniform>()(size, a, b);
    std::sort(v.begin(), v.end());
    std::uniform_int_distribution<int> dist_index(i, j);
    std::uniform_real_distribution<double> dist_number(a, b);
    while(count-- != 0) v[dist_index(generator)] = dist_number(generator);

    return v;
  };
}
template <> inline auto Gen<int, Distribution::PartiallyOrdered>() {
  return [](size_t size, int a, int b, int count, int i, int j) {
    if(!(i <= j && j <= size)) throw;
    auto generator = CreateGenerator();
    std::vector<int> v = Gen<int, Distribution::Uniform>()(size, a, b);
    std::sort(v.begin(), v.end());
    std::uniform_int_distribution<int> dist_index(i, j);
    std::uniform_int_distribution<int> dist_number(a, b);
    while(count-- != 0) v[dist_index(generator)] = dist_number(generator);

    return v;
  };
}
template <> inline auto Gen<std::string, Distribution::PartiallyOrdered>() {
  return [](size_t size, int max_len, int count, int i, int j) {
    if(!(i <= j && j <= size)) throw;
    auto generator = CreateGenerator();
    std::vector<std::string> v = Gen<std::string, Distribution::Uniform>()(size, max_len);
    std::sort(v.begin(), v.end());
    std::uniform_int_distribution<char> distribution('a', 'z');
    std::uniform_int_distribution<int> dist_index(i, j);

    while(count-- != 0) {
      int len = std::uniform_int_distribution<int>(1, max_len)(generator);
      int index = dist_index(generator);
      v[index].clear();
      for (int i = 0; i < len; ++i) {
        v[index].push_back(distribution(generator));
      }
    }
    return v;
  };
}
template<> inline auto Gen<Date, Distribution::PartiallyOrdered>() {
  return [](size_t size, int min_year, int max_year, int count, int i, int j) {
    if(!(i <= j && j <= size)) throw;
    auto generator = CreateGenerator();
    std::vector<Date> v = Gen<Date, Distribution::Uniform>()(size, min_year, max_year);
    std::uniform_int_distribution<int> dist_index(i, j);
    std::sort(v.begin(), v.end());
    std::uniform_int_distribution<int> year_dis(min_year, max_year);
    std::uniform_int_distribution<int> month_dis(1, 12);
    while(count-- != 0) {
      int year = year_dis(generator);
      int month = month_dis(generator);
      int day = 1;
    
      // Определяем количество дней в месяце
      if (month == 2) {
        if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) {
          day = 29;
        } else {
          day = 28;
        }
      } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        day = 30;
      } else {
        day = 31;
      }

      std::uniform_int_distribution<int> day_dis(1, day);
      day = day_dis(generator);

      v[dist_index(generator)] = Date(year, month, day);
    }
    return v;
  };
}
template <> inline auto Gen<digit, Distribution::PartialMixing>() {
  return [](size_t size, int count, int a, int b) {
    if(!(a <= b && b <= size)) throw;
    auto generator = CreateGenerator();
    std::vector<char> v(size);
    std::uniform_int_distribution<char> distribution_for_count(0, size);
    int index_digit[10];
    for(int i = 0; i < 10; ++i) {
      index_digit[i] = distribution_for_count(generator);
    }
    
    std::sort(index_digit, index_digit+10);
    int count_digit[10];
    count_digit[0] = index_digit[0];
    int sum = count_digit[0];
    for(int i = 1; i < 9; ++i) {
      count_digit[i] = index_digit[i] - index_digit[i-1];
      sum += count_digit[i];
    }
    count_digit[9] = size - sum;
    int i = 0;
    auto it = v.begin();
    while(it != v.end() && i != 10) {
      if(count_digit[i] != 0) {
        *it = i + '0';
        it++;
        count_digit[i]--;
      } else i++;
    }
    std::uniform_int_distribution<int> distribution(a, b);
    while(count-- != 0) {
      std::swap(v[distribution(generator)], v[distribution(generator)]);
    }
    

    return v;
  };
}

template <> inline auto Gen<double, Distribution::PartialMixing>() {
  return [](size_t size, double a, double b, int count, int i, int j) {
    if(!(i <= j && j <= size)) throw;
    auto generator = CreateGenerator();
    std::vector<double> v = Gen<double, Distribution::Uniform>()(size, a, b);
    std::sort(v.begin(), v.end());
    std::uniform_int_distribution<int> dist_index(i, j);
    while(count-- != 0) std::swap(v[dist_index(generator)], v[dist_index(generator)]);

    return v;
  };
}
template <> inline auto Gen<int, Distribution::PartialMixing>() {
  return [](size_t size, int a, int b, int count, int i, int j) {
    if(!(i <= j && j <= size)) throw;
    auto generator = CreateGenerator();
    std::vector<int> v = Gen<int, Distribution::Uniform>()(size, a, b);
    std::sort(v.begin(), v.end());
    std::uniform_int_distribution<int> dist_index(i, j);
    while(count-- != 0) std::swap(v[dist_index(generator)], v[dist_index(generator)]);

    return v;
  };
}
template <> inline auto Gen<std::string, Distribution::PartialMixing>() {
  return [](size_t size, int max_len, int count, int i, int j) {
    if(!(i <= j && j <= size)) throw;
    auto generator = CreateGenerator();
    std::vector<std::string> v = Gen<std::string, Distribution::Uniform>()(size, max_len);
    std::sort(v.begin(), v.end());
    std::uniform_int_distribution<int> dist_index(i, j);

    while(count-- != 0) {
      std::swap(v[dist_index(generator)], v[dist_index(generator)]);
    }
    return v;
  };
}
template<> inline auto Gen<Date, Distribution::PartialMixing>() {
  return [](size_t size, int min_year, int max_year, int count, int i, int j) {
    if(!(i <= j && j <= size)) throw;
    auto generator = CreateGenerator();
    std::vector<Date> v = Gen<Date, Distribution::Uniform>()(size, min_year, max_year);
    std::uniform_int_distribution<int> dist_index(i, j);
    std::sort(v.begin(), v.end());
    while(count-- != 0) {
      std::swap(v[dist_index(generator)], v[dist_index(generator)]);
    }
    return v;
  };
}
