#include <stdio.h>
#include <stdbool.h>

bool upordown(int *other)
{
    int x;
    
    if (!other)
    {
        return upordown(&x);
    } else {
        return &x > other;
    }
}

bool upordown1()
{
    int x, y = 0;
    if (&x > &y) { return true; }
    
    return false;
}

int main(int argc, char const *argv[])
{
    printf("upordown1: %s\n", upordown1() ? "Up" : "Down");
    printf("upordown2: %s\n", upordown(NULL) ? "Up" : "Down");
    return 0;
}
