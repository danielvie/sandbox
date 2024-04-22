#pragma once
#include <chrono>
#include <concepts>
#include <string>
#include <string_view>

inline std::string rank(std::integral auto n){
    return std::to_string(n)
        + (n == 2 ? "nd" : n == 3 ? "rd" : "th");
}

inline constexpr std::string_view to_day_name(unsigned encoding){
    constexpr std::string_view days[]
        { "Sunday", "Monday", "Thuesday", "Wednesday",
          "Thursday", "Friday", "Saturday" };
    return days[encoding%7]; // in iso_encoding 7 is Sunday.
}

std::string to_string(const std::chrono::year_month_day& day_based){
    auto year = day_based.year();
    auto month = day_based.month();
    auto day = day_based.day();

    std::chrono::year_month_weekday weekday_based{day_based};
    auto weekday_indexed = weekday_based.weekday_indexed();
    auto weekday = weekday_based.weekday();

    std::ostringstream os;
    os << to_day_name(weekday.c_encoding())
       << "[" << rank(uint(weekday_indexed.index())) << "] "
       << uint(day) << '/' << uint(month) << '/' << int(year);
    return os.str();
}

inline std::string to_string(
        const std::chrono::year_month_day_last& day_last){
    return to_string(std::chrono::year_month_day{day_last});
}

inline std::string to_string(
        const std::chrono::year_month_weekday_last& week_last){
    return to_string(std::chrono::year_month_day{week_last});
}

inline std::string to_string(
        const std::chrono::year_month_weekday& week_based){
    return to_string(std::chrono::year_month_day{week_based});
}
