#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "chrono_helper.h"
#include "tools.h"

int main(){
    using namespace std::literals::chrono_literals;
    //constexpr std::string_view days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sunny"};

    // y/m/d
    // m/d/y
    // d/m/y

    auto some_day = std::chrono::Saturday[2] / std::chrono::February / 2021;
    static_assert(std::same_as<std::chrono::year_month_weekday,decltype(some_day)>);
    std::cout << to_string(some_day) << '\n';
    std::cout << to_string(std::chrono::January/1/1970y) << '\n';
    std::cout << to_string(1d/std::chrono::January/1970y) << '\n';
    std::cout << to_string(21d/std::chrono::June/2020y) << '\n';
    std::cout << to_string(1d/std::chrono::September/1985) << '\n';
    {
        using namespace std::chrono;
        std::cout << to_string(1d/September/1985) << '\n';
        std::cout << to_string(September/1/1985) << '\n';
        std::cout << to_string(1985y/September/1) << '\n';

        std::cout << to_string(last/February/2020) << '\n';
        std::cout << to_string(Friday[2]/February/2020) << '\n';
        std::cout << to_string(Friday[last]/February/2020) << '\n';
    }
    auto m = std::chrono::Saturday[std::chrono::last]/std::chrono::January/2020;
    for(auto x: std::vector<int>(12)){
        std::cout << to_string(m) << '\n';
        auto d = std::chrono::year_month_weekday{m};
        std::cout << rank(d.index()) << '\n';
        m = { m.year(), m.month() + std::chrono::months(1), m.weekday_last() };
    }

    {
        using namespace std::chrono;
        auto m = 23d/January/2020;
        for(auto x: std::vector<int>(12)){
            std::cout << to_string(m) << '\n';
            auto d = std::chrono::year_month_weekday{m};
            std::cout << to_day_name(d.weekday().c_encoding()) << '\n';
            m = { m.year(), m.month() + months(1), m.day() };
        }
    }

    {
        using namespace std::chrono;
        auto m = last/January/2020;
        for(auto x: std::vector<int>(12)){
            std::cout << to_string(m) << '\n';
            auto d = year_month_day{m};
            std::cout << unsigned(d.day()) << '\n';
            m = { m.year(), month_day_last{m.month() + months(1)} };
        }
    }


    auto last_saturday = std::chrono::Saturday[std::chrono::last] / std::chrono::February / 2021y;
    static_assert(std::same_as<std::chrono::year_month_weekday_last,decltype(last_saturday)>);
    static_assert(std::same_as<unsigned, uint>);

    //auto bevrijdingsdag =  std::chrono::Saturday[1] / std::chrono::May / 1945;
    auto bevrijdingsdag =  std::chrono::May/5/1945;
    auto wanneer = std::chrono::year_month_weekday{bevrijdingsdag};
    auto hoeveelste = wanneer.index();
    auto wat_voor_een_iso = wanneer.weekday().iso_encoding();
    auto wat_voor_een_c = wanneer.weekday().c_encoding();
    // index is zoveelste 
    std::cout << to_day_name(wat_voor_een_iso) << "[" << hoeveelste << "]" << '\n';
    std::cout << to_day_name(7) << "[" << hoeveelste << "]" << '\n';
    std::cout << to_day_name(14) << "[" << hoeveelste << "]" << '\n';
    std::cout << wat_voor_een_iso << '\n';
    std::cout << wat_voor_een_c << '\n';

    //std::cout << some_day;
    std::cout << some_day.weekday_indexed().index() << '\n';
    std::cout << some_day.index() << '\n';
    //std::cout << some_day.weekday() << '\n';
    auto other_day =  std::chrono::year_month_day { some_day };
    std::cout << static_cast<unsigned>(other_day.day()) << '\n';

    auto other_satur_day =  std::chrono::year_month_day { last_saturday };
    std::cout << static_cast<unsigned>(other_satur_day.day()) << '\n';
    {
        using namespace std::chrono;
        //auto result = clock_cast<utc_clock>(system_clock::now());
        year_month_day today{time_point_cast<days>(system_clock::now())};
        std::cout << to_string(today) << '\n';
        std::cout << static_cast<int>(today.year()) << '/'
              << static_cast<unsigned>(today.month()) << '/'
              << static_cast<unsigned>(today.day()) << '\n';
        //try {
        //    const zoned_time amsterdam_time { "Europe/Amsterdam",
        //                                    system_clock::now() };
        //} catch (nonexistent_local_time& ex){
        //    std::cout << ex.what();
        //}
    }
}
