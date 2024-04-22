#include <iostream>
#include "libcoro/include/coro/generator.hpp"

coro::generator<int> fibonatti()
{
  int a = 0, b = 1;
  while (true)
  {
    co_yield b;
    auto tmp = a; a = b; b += tmp;
  }
}

int main(int argc, char **argv)
{
  for (auto i : fibonatti())
  {
    if (i > 1'000'000) break;
    std::cout << i << std::endl;
  }
}
