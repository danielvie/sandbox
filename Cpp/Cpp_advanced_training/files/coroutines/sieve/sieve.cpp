#include <iostream>
#include "libcoro/include/coro/generator.hpp"

coro::generator<int> sieve()
{
    bool V[100];
    for (int i = 0; i < 100; i++)
    {
        V[i] = true;
    }

    int i = 2;
    while (i < 100)
    {
        // return value
        co_yield i;

        // mark false on numbers and increment to next
        int n = i+i;
        while (n < 100)
        {
            V[n] = false;
            n += i;
        }
        i++;

        // skip numbers that are false
        while(V[i]==false && i<100)
        {
            i++;
        }
    }
    // code inspired by Eratosthenes
}

int main(int argc, char **argv)
{
    for (auto i : sieve())
        std::cout << i << std::endl;
}
