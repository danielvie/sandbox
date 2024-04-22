#include <chrono>
#include <iostream>
#include <iterator>
#include <numbers>
#include <string_view>
#include <version>

#if __cpp_lib_format >= 201907L
#include <format>
namespace f = std;
#else
#include <fmt/chrono.h>
#include <fmt/format.h>
namespace f = fmt;
#endif

int main(){
    using namespace std::literals;
    std::ostream_iterator<char> o_it(std::cout);
    f::format_to(o_it, "{}\n"sv, "o_it");
    std::cout << f::format("{}"sv, 7) << '\n';
    std::cout << f::format("{}/{}"sv, 7, 8) << '\n';
    std::cout << f::format("{1}/{0}"sv, 7, 8) << '\n';
    //std::cout << f::format("{1}/{}"sv, 7, 8) << '\n'; // Don't mix
    std::cout << f::format("{:6}"sv, 7) << '\n';
    std::cout << f::format("{:<6}"sv, 7) << '\n';
    std::cout << f::format("{:>6}"sv, 7) << '\n';
    std::cout << f::format("{:^6}"sv, 7) << '\n';
//    std::cout << f::format("{:=06}"sv, -7) << '\n';
    std::cout << f::format("{:=<6}"sv, 7) << '\n';
    std::cout << f::format("{:=>6}"sv, 7) << '\n';
    std::cout << f::format("{:=^6}"sv, 7) << '\n';
    // = pushes out the fill char
//    std::cout << f::format("{:==06}"sv, -7) << '\n';
    for(auto fill_style: "<>^"sv){
        std::cout << f::vformat(//
                f::format("{0} {{:%{0}10}}"sv, fill_style),//
                f::make_format_args(7)) << '\n';
    }
    for(auto base_style: "bBdoxX"sv){
        std::cout << f::vformat(//
            f::format("{0} {{0:<6{0}}}{{0:#{0}}}\n"sv, base_style),//
            f::make_format_args(22));
    }

    using namespace std::numbers;
    std::cout << f::format("#{}#\n"sv, pi);
    std::cout << f::format("#{}#\n"sv, pi);
    std::cout << f::format("#{:+}#\n"sv, pi);
    std::cout << f::format("#{: }#\n"sv, pi);
    std::cout << f::format("#{:-}#\n"sv, pi);
    std::cout << f::format("#{:20}#\n"sv, pi);
    std::cout << f::format("#{:20.4}#\n"sv, pi);
    std::cout << f::format("#{:{}.{}}#\n"sv, pi, 20, 4);
    std::cout << f::format("#{0:{2}.{1}}#\n"sv, pi, 4, 20);
    //std::cout << f::format("#{:{2}.{1}}#\n"sv, pi, 4, 20); // Don't mix
    constexpr auto π = pi;
    for(auto base_style: "aAeEfFgG"sv){
        std::cout << f::vformat(//
                f::format("{0} {{:10{0}}}\n"sv, base_style),//
                f::make_format_args(e));
    }
    std::cout << f::vformat("{}"sv, f::make_format_args(7)) << '\n';
    std::cout << f::format("{}", 7) << '\n';
    std::cout << f::format("{}", 7ms) << '\n';
    std::cout << f::format("{:_^12}", 7ms) << '\n';
    std::cout << f::format("{:%H:%M}", 7h+10min) << '\n';
    //std::cout << f::format("{:s}\n", 7); // Not a string
    //std::cout << f::format("{}",//
    //        std::chrono::system_clock::now()) << '\n'; // Not available 
}
