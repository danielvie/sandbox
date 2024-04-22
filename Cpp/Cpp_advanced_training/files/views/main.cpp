#include <iostream>
#include <algorithm>
#include <ranges>
#include <vector>

#include "is_prime.h"

using namespace std::ranges::views;

int main(int argc, char **argv) {

    auto numbers = iota(10'000)
        | filter(is_prime())
        | take(20);

    std::ranges::copy(numbers, std::ostream_iterator<int>(std::cout, "\n"));

    return 0;
}