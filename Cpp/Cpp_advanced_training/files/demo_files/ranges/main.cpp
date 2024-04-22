#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>
#include <string>
#include <sstream>
#include <vector>

int main(){
    using namespace std::literals;
    namespace r = std::ranges;

    std::vector greetings { "hello"s, "goodbye"s,//
        "wiedersehen"s, "tot ziens"s, "bye bye"s };

    r::sort(greetings);

    static_assert(r::range<std::vector<std::string>>);
    static_assert(r::range<std::string>);
    static_assert(r::range<int[7]>);
    static_assert( ! r::range<int[]>);

    auto exclaim = [](auto s){ return s + "!"; };
    std::vector<std::string> strong_greetings(greetings.size());
    r::transform(greetings,//
        strong_greetings.begin(), exclaim);
    r::transform(greetings.begin(), greetings.end(),//
        strong_greetings.begin(), exclaim);

    auto add_num = [](auto s, auto t)//
        { return std::to_string(t) + ' ' +s; };
    std::vector<int> numbers;
    r::copy(r::iota_view<int, int>(0, greetings.size()),//
        std::back_inserter(numbers));

    std::vector<std::string> numbered_greetings(greetings.size());
    r::transform(greetings, numbers,//
        numbered_greetings.begin(), add_num);
    r::transform(greetings.begin(), greetings.end(),//
        numbers.begin(), numbers.end(),//
        numbered_greetings.begin(), add_num);

    r::copy(numbered_greetings,//
        std::ostream_iterator<std::string>(std::cout, "\n"));

    std::istringstream input{"hello you"};
    r::copy(r::istream_view<std::string>(input),//
        std::ostream_iterator<std::string>(std::cout, "\n"));

    static_assert(r::common_range<std::vector<std::string>>);
    auto s = r::istream_view<std::string>(input); // NOT a type
    static_assert(r::range<decltype(s)>);
    static_assert( ! r::common_range<decltype(s)>);
}
    
