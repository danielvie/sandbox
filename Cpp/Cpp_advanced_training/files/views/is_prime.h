#pragma once
#include <concepts>
struct is_prime
{
    template <std::integral N>
    bool operator()(N x)
    {
        for (N d{2}; d * d <= x; ++d)
        {
            if (x % d == 0)
                return false;
        }
        return true;
    }
};