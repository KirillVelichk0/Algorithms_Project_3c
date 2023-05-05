#pragma once
#include <algorithm>
#include <cstdint>
#include <climits>
#include <string>
auto GetDigitMapper(){
    auto mapper = [](char digit){
        std::uint64_t result = -1 * SCHAR_MIN ;
        result += digit;
        return result;
    };
    return mapper;
}

auto GetIntMapper(){
    auto mapper = [](int number){
        std::uint64_t result = 0;
        result -= INT32_MIN;
        result += number;
        return result;
    };
    return mapper;
}

auto GetStringMapper(){
    auto mapper = [](const std::string& someStr){
        std::uint64_t result = 0;
        std::for_each(someStr.cbegin(), someStr.cend(), [&result](const char symb){
            std::uint64_t curVal = -1 * SCHAR_MIN;
            curVal += symb;
            result += curVal;
        });
        return result;
    };
    return mapper;
}

auto GetDateMapper(){
    auto mapper = [](const auto& date){
        std::uint64_t result = 0;
        result += date.day();
        result += date.month() * 30;
        result += date.year() * 30 * 12;
        return result;
    };
    return mapper;
}